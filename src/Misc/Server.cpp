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
#include <Misc/MessageParser.hpp>
#include <Misc/Server.hpp>
#include <Static/ENetInitializer.hpp>
#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Server::Server(std::uint16_t port, std::uint32_t timeoutTime) : port(port), timeoutTime(timeoutTime), enetHost(nullptr)
{
	if (!port)
	{
		throw InvalidNetworkPortException(port);
	}
	ENetInitializer::Initialize();
	AddMessageParser<WhackAStoodentServer::Messages::ErrorMessage>
	(
		[](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::ErrorMessage& message)
		{
			peer->OnErrorReceived(message.GetErrorType(), message.GetErrorMessage());
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::AuthenticateMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::AuthenticateMessage& message)
		{
			uuids::uuid user_id(message.GetUserID());
			std::wstring name(message.GetUsername());
			if (users.contains(peer->GetIncomingPeerID()))
			{
				peer->SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(EErrorType::InvalidMessageContext, L"You are already authenticated.");
			}
			else if (!user_id.is_nil() && userIDToPeerIDLookup.contains(user_id))
			{
				peer->SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(EErrorType::Internal, L"User ID is already occupied.");
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
				std::string session_code;
				while (sessionCodeToUserIDLookup.contains(SessionCodes::CreateSessionCode(session_code)));
				std::shared_ptr<WhackAStoodentServer::User> user(std::make_shared<WhackAStoodentServer::User>(peer, user_id, name, session_code, 0L));
				sessionCodeToUserIDLookup.insert_or_assign(session_code, user);
				user->OnConnected += [&, user]()
				{
					OnUserConnected(user);
				};
				user->OnDisconnected += [&, user]()
				{
					OnUserDisconnected(user);
				};
				users.insert_or_assign(peer->GetIncomingPeerID(), user);
				user->OnConnected();
			}
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::PingMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::PingMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[peer, messageData(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					std::int32_t ping_data(messageData.GetPingData());
					user->OnPingReceived(ping_data);
					peer->SendPeerMessage<WhackAStoodentServer::Messages::PongMessage>(ping_data);
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::PongMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::PongMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[messageData(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					std::int32_t pong_data(messageData.GetPongData());
					user->OnPongReceived(pong_data);
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::GetMatchHistoryMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::GetMatchHistoryMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[peer](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					std::vector<WhackAStoodentServer::MatchHistoryEntry> match_history;
					user->OnMatchHistoryRequested();
					// TODO: Get match history
					peer->SendPeerMessage<WhackAStoodentServer::Messages::MatchHistoryMessage>(match_history);
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::PlayWithRandomMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::PlayWithRandomMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					// TODO: Find someone to match with
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::PlayWithSessionCodeMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::PlayWithSessionCodeMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[&, currentMessage(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					if (currentMessage.GetSessionCode() == user->GetSessionCode())
					{
						// TODO: Error
					}
					else
					{
						auto session_code_to_user_id_lookup_iterator(sessionCodeToUserIDLookup.find(currentMessage.GetSessionCode()));
						if (session_code_to_user_id_lookup_iterator == sessionCodeToUserIDLookup.end())
						{
							// TODO: Error
						}
						else
						{
							// TODO: Find session to match with
						}
					}
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::AcceptPlayRequestMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::AcceptPlayRequestMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					// TODO: Process user accepting play request
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::DenyPlayRequestMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::DenyPlayRequestMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					// TODO: Process user denying play request
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::LoadedGameMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::LoadedGameMessage& message)
		{
			AssertPeerIsInGame
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					// TODO: Process user loaded game
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::HitMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::HitMessage& message)
		{
			AssertPeerIsInGame
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					// TODO: Process user loaded game
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::LookMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::LookMessage& message)
		{
			AssertPeerIsInGame
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					// TODO: Process user looking
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::HideMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::HideMessage& message)
		{
			AssertPeerIsInGame
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					// TODO: Process user hiding
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
	AddMessageParser<WhackAStoodentServer::Messages::LogMessage>
	(
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, const WhackAStoodentServer::Messages::LogMessage& message)
		{
			AssertPeerIsAuthenticated
			(
				peer,
				[](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					// TODO: Log message
				}
			);
		},
		[&](std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
		{
			HandleMessageParseFailedEvent(peer, message);
		}
	);
}

WhackAStoodentServer::Server::~Server()
{
	WhackAStoodentServer::ENetInitializer::Deinitialize();
}

bool WhackAStoodentServer::Server::Start()
{
	bool ret(false);
	std::size_t ban_count(bans.LoadFromFile(defaultBansPath));
	if (ban_count)
	{
		std::cout << "Successfully loaded " << ban_count << " " << ((ban_count == static_cast<std::size_t>(1)) ? "ban" : "bans") << " from \"" << defaultBansPath << "\"." << std::endl;
	}
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
		bans.SaveToFile(defaultBansPath);
		for (auto& peer : peers)
		{
			peer.second->Disconnect(WhackAStoodentServer::EDisconnectionReason::Stopped);
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
						peer->OnConnectionAttempted += [&, peer]()
						{
							OnPeerConnectionAttempted(peer);
						};
						peer->OnConnected += [&, peer]()
						{
							OnPeerConnected(peer);
						};
						peer->OnDisconnected += [&, peer]()
						{
							OnPeerDisconnected(peer);
						};
						peer->OnConnectionAttempted();
						if (bans.IsIPAddressBanned(peer->GetIPv4Address()))
						{
							peer->Disconnect(WhackAStoodentServer::EDisconnectionReason::Banned);
						}
						else
						{
							peer->OnConnected();
						}
					}
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					{
						auto users_iterator = users.find(enet_event.peer->incomingPeerID);
						auto peers_iterator = peers.find(enet_event.peer->incomingPeerID);
						if (users_iterator != users.end())
						{
							users_iterator->second->OnDisconnected();
							userIDToPeerIDLookup.erase(users_iterator->second->GetUserID());
							users.erase(users_iterator);
						}
						if (peers_iterator != peers.end())
						{
							peers_iterator->second->OnDisconnected();
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
								std::shared_ptr<WhackAStoodentServer::Peer> peer(peers_iterator->second);
								std::shared_ptr<WhackAStoodentServer::Message> message(std::make_shared<WhackAStoodentServer::Message>(enet_event.packet->data, enet_event.packet->dataLength));
								WhackAStoodentServer::EMessageType message_type(message->GetMessageType());
								auto message_parser_list_iterator(messageParserLists.find(message_type));
								if (message_parser_list_iterator == messageParserLists.end())
								{
									peer->OnUnsupportedMessageTypeReceived(message_type);
									peer->SendPeerMessage<Messages::ErrorMessage>(EErrorType::UnsupportedMessageType, L"Unsupported message type \"" + std::to_wstring(static_cast<int>(message_type)) + L"\" has been received.");
								}
								else
								{
									peer->OnMessageReceived(message);
									for (const auto& message_parser : message_parser_list_iterator->second)
									{
										message_parser->ParsePeerMessage(peer, message);
									}
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
					std::cerr << "Invalid ENet event type \"" << enet_event.type << "\"" << std::endl;
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

/// <summary>
/// Gets bans
/// </summary>
/// <returns>Bans</returns>
WhackAStoodentServer::Bans& WhackAStoodentServer::Server::GetBans()
{
	return bans;
}

/// <summary>
/// Gets bans
/// </summary>
/// <returns>Bans</returns>
const WhackAStoodentServer::Bans& WhackAStoodentServer::Server::GetBans() const
{
	return bans;
}

void WhackAStoodentServer::Server::HandleMessageParseFailedEvent(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
{
	peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::MalformedMessage, L"Failed to parse message type \"" + std::to_wstring(static_cast<int>(message->GetMessageType())) + L"\"");
}

void WhackAStoodentServer::Server::AssertPeerIsAuthenticated(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user)> onPeerIsAuthenticated)
{
	auto user_iterator(users.find(peer->GetIncomingPeerID()));
	if (user_iterator == users.end())
	{
		peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are not authenticated.");
	}
	else
	{
		onPeerIsAuthenticated(user_iterator->second);
	}
}

void WhackAStoodentServer::Server::AssertPeerIsInGame(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)> onPeerIsInGame)
{
	AssertPeerIsAuthenticated
	(
		peer,
		[](std::shared_ptr<WhackAStoodentServer::User> user)
		{
			// TODO: Assert that peer is in game
		}
	);
}
