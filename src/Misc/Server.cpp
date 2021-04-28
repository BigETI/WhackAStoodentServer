#include <iostream>
#include <span>

#include <enet/enet.h>

#include <Enumerators/EMessageType.hpp>
#include <Exceptions/ENetInitializationFailedException.hpp>
#include <Exceptions/InvalidNetworkPortException.hpp>
#include <Messages/AcceptPlayRequestMessage.hpp>
#include <Messages/AcknowledgeAuthentificationMessage.hpp>
#include <Messages/AuthenticateMessage.hpp>
#include <Messages/DenyPlayRequestMessage.hpp>
#include <Messages/ErrorMessage.hpp>
#include <Messages/GetMatchHistoryMessage.hpp>
#include <Messages/HideMessage.hpp>
#include <Messages/HitMessage.hpp>
#include <Messages/LoadedGameMessage.hpp>
#include <Messages/LogMessage.hpp>
#include <Messages/LookMessage.hpp>
#include <Messages/MatchHistoryMessage.hpp>
#include <Messages/PingMessage.hpp>
#include <Messages/PlayWithRandomMessage.hpp>
#include <Messages/PlayWithSessionCodeMessage.hpp>
#include <Messages/PongMessage.hpp>
#include <Misc/MatchHistoryEntry.hpp>
#include <Misc/Message.hpp>
#include <Misc/Server.hpp>
#include <Static/ENetInitializer.hpp>
#include <Static/Rules.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Server::Server(std::uint16_t port, std::uint32_t timeoutTime) : port(port), timeoutTime(timeoutTime), enetHost(nullptr)
{
	if (!port)
	{
		throw InvalidNetworkPortException(port);
	}
	ENetInitializer::Initialize();
}

WhackAStoodentServer::Server::~Server()
{
	ENetInitializer::Deinitialize();
}

bool WhackAStoodentServer::Server::Start()
{
	bool ret(false);
	if (!enetHost)
	{
		ENetAddress enet_address;
		enet_address_set_host(&enet_address, "localhost");
		enet_address.port = port;
		enetHost = enet_host_create
		(
			&enet_address,
			static_cast<std::size_t>(ENET_PROTOCOL_MAXIMUM_PEER_ID),
			static_cast<std::size_t>(ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT),
			static_cast<enet_uint32>(0),
			static_cast<enet_uint32>(0)
		);
		ret = !!enetHost;
	}
	return ret;
}

void WhackAStoodentServer::Server::Stop()
{
	if (enetHost)
	{
		for (auto& peer : peers)
		{
			peer.second->Disconnect(EDisconnectionReason::Stopped);
		}
		enet_host_destroy(enetHost);
		enetHost = nullptr;
	}
}

bool WhackAStoodentServer::Server::IsRunning() const
{
	return !!enetHost;
}

bool WhackAStoodentServer::Server::ProcessMessages()
{
	bool ret(false);
	if (enetHost)
	{
		bool is_polling(true);
		ENetEvent enet_event;
		while (is_polling)
		{
			int host_service_result(enet_host_service(enetHost, &enet_event, timeoutTime));
			is_polling = (host_service_result > 0);
			if (is_polling)
			{
				switch (enet_event.type)
				{
				case ENET_EVENT_TYPE_NONE:
					// ...
					break;
				case ENET_EVENT_TYPE_CONNECT:
					{
						std::shared_ptr<WhackAStoodentServer::Peer> peer(std::make_shared<WhackAStoodentServer::Peer>(enet_event.peer));
						peers.insert_or_assign(enet_event.peer->incomingPeerID, peer);
						OnPeerConnectionAttempted(peer);
					}
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					{
						auto users_iterator = users.find(enet_event.peer->incomingPeerID);
						auto peers_iterator = peers.find(enet_event.peer->incomingPeerID);
						if (users_iterator != users.end())
						{
							OnUserDisconnected(users_iterator->second);
							userIDToPeerIDLookup.erase(users_iterator->second->GetUserID());
							users.erase(users_iterator);
						}
						if (peers_iterator != peers.end())
						{
							OnPeerDisconnected(peers_iterator->second);
							peers.erase(peers_iterator);
						}
					}
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					{
						auto peers_iterator(peers.find(enet_event.peer->incomingPeerID));
						if (peers_iterator != peers.end())
						{
							try
							{
								std::shared_ptr<WhackAStoodentServer::Message> message(std::make_shared<WhackAStoodentServer::Message>(enet_event.packet->data, enet_event.packet->dataLength, peers_iterator->second));
								OnPeerMessageReceived(message);
								switch (message->GetMessageType())
								{
								case EMessageType::Error:
									{
										WhackAStoodentServer::Messages::ErrorMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process error message
										}
									}
									break;
								case EMessageType::Authenticate:
									{
										WhackAStoodentServer::Messages::AuthenticateMessage message_data;
										if (message->TryGetData(message_data))
										{
											uuids::uuid user_id(message_data.GetUserID());
											std::wstring name(message_data.GetUsername());
											
											if (users.contains(message->GetPeer().GetIncomingID()))
											{
												// TODO: Notify user that it is already authenticated
											}
											else if (!user_id.is_nil() && userIDToPeerIDLookup.contains(user_id))
											{
												// TODO: Notify error
											}
											else
											{
												while (user_id.is_nil())
												{
													WhackAStoodentServer::UUIDs::CreateNewUUID(user_id);
													if (userIDToPeerIDLookup.contains(user_id))
													{
														user_id = uuids::uuid();
													}
												}
												if (name.length() > WhackAStoodentServer::Rules::MaximalNameLength)
												{
													name = name.substr(static_cast<std::size_t>(0), WhackAStoodentServer::Rules::MaximalNameLength);
												}
												std::shared_ptr<WhackAStoodentServer::User> user(std::make_shared<WhackAStoodentServer::User>(peers_iterator->second, user_id, name, 0L));
												users.insert_or_assign(message->GetPeer().GetIncomingID(), user);
												OnUserAuthenticated(user);
											}
										}
									}
									break;
								case EMessageType::Ping:
									{
										WhackAStoodentServer::Messages::PingMessage message_data;
										if (message->TryGetData(message_data))
										{
											auto user_iterator(users.find(message->GetPeer().GetIncomingID()));
											if (user_iterator == users.end())
											{
												// TODO: Error
											}
											else
											{
												std::int32_t ping_data(message_data.GetPingData());
												OnUserPingReceived(user_iterator->second, ping_data);
												message->GetPeer().SendPeerMessage<Messages::PongMessage>(ping_data);
											}
										}
									}
									break;
								case EMessageType::Pong:
									{
										WhackAStoodentServer::Messages::PongMessage message_data;
										if (message->TryGetData(message_data))
										{
											auto user_iterator(users.find(message->GetPeer().GetIncomingID()));
											if (user_iterator == users.end())
											{
												// TODO: Error
											}
											else
											{
												std::int32_t pong_data(message_data.GetPongData());
												OnUserPongReceived(user_iterator->second, pong_data);
											}
										}
									}
									break;
								case EMessageType::GetMatchHistory:
									{
										WhackAStoodentServer::Messages::GetMatchHistoryMessage message_data;
										if (message->TryGetData(message_data))
										{
											std::vector<WhackAStoodentServer::MatchHistoryEntry> match_history;
											// TODO: Fetch match history
											message->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::MatchHistoryMessage>(match_history);
										}
									}
									break;
								case EMessageType::PlayWithRandom:
									{
										WhackAStoodentServer::Messages::PlayWithRandomMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Find someone to match with
										}
									}
									break;
								case EMessageType::PlayWithSessionCode:
									{
										WhackAStoodentServer::Messages::PlayWithSessionCodeMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Find session to match with
										}
									}
									break;
								case EMessageType::AcceptPlayRequest:
									{
										WhackAStoodentServer::Messages::AcceptPlayRequestMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user accepting play request
										}
									}
									break;
								case EMessageType::DenyPlayRequest:
									{
										WhackAStoodentServer::Messages::DenyPlayRequestMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user denying play request
										}
									}
									break;
								case EMessageType::LoadedGame:
									{
										WhackAStoodentServer::Messages::LoadedGameMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user loaded game
										}
									}
									break;
								case EMessageType::Hit:
									{
										WhackAStoodentServer::Messages::HitMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user loaded game
										}
									}
									break;
								case EMessageType::Look:
									{
										WhackAStoodentServer::Messages::LookMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user looking
										}
									}
									break;
								case EMessageType::Hide:
									{
										WhackAStoodentServer::Messages::HideMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Process user hiding
										}
									}
									break;
								case EMessageType::Log:
									{
										WhackAStoodentServer::Messages::LogMessage message_data;
										if (message->TryGetData(message_data))
										{
											// TODO: Log message
										}
									}
									break;
								default:
									// TODO: Notify error
									break;
								}
							}
							catch (const std::exception& e)
							{
								std::cerr << e.what() << std::endl;
							}
						}
						enet_packet_destroy(enet_event.packet);
					}
					break;
				default:
					// TODO: Notify error
					break;
				}
			}
			else if (host_service_result < 0)
			{
				std::cerr << "Failed to poll events from ENet." << std::endl;
			}
			ret = (host_service_result >= 0);
		}
	}
	return ret;
}
