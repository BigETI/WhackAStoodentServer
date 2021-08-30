#include <iostream>
#include <span>

#include <Enumerators/EMessageType.hpp>
#include <Enumerators/EPlayerRole.hpp>
#include <Exceptions/ENetInitializationFailedException.hpp>
#include <Exceptions/ENetPeerSendFailedException.hpp>
#include <Exceptions/InvalidNetworkPortException.hpp>
#include <Messages/AcceptPlayRequestMessage.hpp>
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
#include <Static/Defaults.hpp>
#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs a server
/// </summary>
/// <param name="port">Network port</param>
/// <param name="timeoutTime">Timeout time</param>
WhackAStoodentServer::Server::Server(std::uint16_t port, std::uint32_t timeoutTime) :
	port(port),
	timeoutTime(timeoutTime),
	enetHost(nullptr),
	networkingThread(nullptr),
	isNetworkingThreadRunning(false)
{
	if (!port)
	{
		throw WhackAStoodentServer::InvalidNetworkPortException(port);
	}
	WhackAStoodentServer::ENetInitializer::Initialize();
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
			std::wstring username(message.GetUsername());
			if (lobby.IsPeerAnUser(peer))
			{
				peer->SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(EErrorType::InvalidMessageContext, L"You are already authenticated.");
			}
			else if (!user_id.is_nil() && lobby.IsUserIDOccupied(user_id))
			{
				std::cout << user_id << std::endl;
				peer->SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(EErrorType::Internal, L"User ID is already occupied.");
			}
			else
			{
				while (user_id.is_nil())
				{
					WhackAStoodentServer::UUIDs::CreateNewUUID(user_id);
					if (lobby.IsUserIDOccupied(user_id))
					{
						user_id = uuids::uuid();
					}
				}
				if (username.length() > WhackAStoodentServer::Rules::MaximalNameLength)
				{
					username = username.substr(static_cast<std::size_t>(0), WhackAStoodentServer::Rules::MaximalNameLength);
				}
				lobby.CreateUser(peer, user_id, username);
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
			AssertPeerIsAuthenticatedAndNotInGame
			(
				peer,
				[&](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					lobby.AddUserToSearch(user);
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
			AssertPeerIsAuthenticatedAndNotInGame
			(
				peer,
				[&, currentMessage(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					std::shared_ptr<WhackAStoodentServer::User> opposing_user;
					if (lobby.TryGetUserFromSessionCode(currentMessage.GetSessionCode(), opposing_user))
					{
						lobby.RequestForPlaying(user, opposing_user);
					}
					else
					{
						std::wstringstream error_message;
						error_message << L"Session code \"";
						for (char character : currentMessage.GetSessionCode())
						{
							error_message << static_cast<wchar_t>(character);
						}
						error_message << L"\" does not exist.";
						peer->SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, error_message.str());
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
				[&](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					lobby.AcceptPlayRequest(user);
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
				[&, messageData(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user)
				{
					lobby.DenyPlayRequest(user, messageData.GetReason());
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
					user->SetGameLoadedState(true);
					game->StartGame();
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
			AssertPeerIsAHitter
			(
				peer,
				[messageData(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					game->Hit(messageData.GetPosition());
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
			AssertPeerIsAMole
			(
				peer,
				[messageData(std::move(message))](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
				{
					game->Look(messageData.GetLookHole());
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
					game->Hide();
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

/// <summary>
/// Destroys server
/// </summary>
WhackAStoodentServer::Server::~Server()
{
	Stop();
	WhackAStoodentServer::ENetInitializer::Deinitialize();
}

/// <summary>
/// Starts this server
/// </summary>
/// <returns>"true" if starting server was successful, otherwise "false"</returns>
bool WhackAStoodentServer::Server::Start()
{
	bool ret(!networkingThread);
	if (ret)
	{
		std::size_t ban_count(bans.LoadFromFile(WhackAStoodentServer::Defaults::BansFilePath));
		if (ban_count)
		{
			std::cout << "Successfully loaded " << ban_count << " " << ((ban_count == static_cast<std::size_t>(1)) ? "ban" : "bans") << " from \"" << WhackAStoodentServer::Defaults::BansFilePath << "\"." << std::endl;
		}
		isNetworkingThreadRunning = true;
		networkingThread = new std::thread(NetworkingThread, this);
	}
	return ret;
}

/// <summary>
/// Stops this server
/// </summary>
void WhackAStoodentServer::Server::Stop()
{
	if (networkingThread)
	{
		bans.SaveToFile(WhackAStoodentServer::Defaults::BansFilePath);
		for (auto& peer : peers)
		{
			peer.second->Disconnect(WhackAStoodentServer::EDisconnectionReason::Stopped);
		}
		isNetworkingThreadRunning = false;
		networkingThread->join();
		networkingThread = nullptr;
	}
}

/// <summary>
/// Is this server running
/// </summary>
/// <returns>"true" if this server is running, otherwise "false"</returns>
bool WhackAStoodentServer::Server::IsRunning() const
{
	return !!enetHost;
}

/// <summary>
/// Processes messages
/// </summary>
/// <returns>"true" if server is still running, otherwise "false"</returns>
bool WhackAStoodentServer::Server::ProcessMessages()
{
	bool ret(networkingThread);
	if (ret)
	{
		{
			ENetPeer* enet_peer;
			while (connectedPeerQueue.TryDequeue(enet_peer))
			{
				std::shared_ptr<WhackAStoodentServer::Peer> peer(std::make_shared<WhackAStoodentServer::Peer>(enet_peer));
				peers.insert_or_assign(enet_peer->incomingPeerID, peer);
				peer->OnConnectionAttempted += [&, peer]()
				{
					std::cout << "Connection attempt from peer ID " << peer->GetIncomingPeerID() << " with IP " << peer->GetIPAddressString() << "." << std::endl;
					OnPeerConnectionAttempted(peer);
				};
				peer->OnConnected += [&, peer]()
				{
					std::cout << "Peer ID " << peer->GetIncomingPeerID() << " with IP " << peer->GetIPAddressString() << " has connected." << std::endl;
					OnPeerConnected(peer);
				};
				peer->OnDisconnected += [&, peer]()
				{
					std::cout << "Peer ID " << peer->GetIncomingPeerID() << " with IP " << peer->GetIPAddressString() << " has been disconnected." << std::endl;
					OnPeerDisconnected(peer);
				};
				peer->OnMessageSent += [&, peer](std::shared_ptr<WhackAStoodentServer::Message> message)
				{
					outgoingMessages.Enqueue(std::make_pair(peer, message));
				};
				peer->OnConnectionAttempted();
				if (bans.IsIPAddressBanned(peer->GetIPAddressString()))
				{
					peer->Disconnect(WhackAStoodentServer::EDisconnectionReason::Banned);
				}
				else
				{
					peer->OnConnected();
				}
			}
		}
		{
			std::uint16_t incoming_peer_id;
			while (disconnectedPeerQueue.TryDequeue(incoming_peer_id))
			{
				auto peers_iterator(peers.find(incoming_peer_id));
				if (peers_iterator != peers.end())
				{
					std::shared_ptr<WhackAStoodentServer::User> user;
					if (lobby.TryGetUserFromPeer(peers_iterator->second, user))
					{
						lobby.RemoveUser(user);
					}
					peers_iterator->second->OnDisconnected();
					peers.erase(peers_iterator);
				}
			}
		}
		{
			std::pair<std::uint16_t, std::shared_ptr<WhackAStoodentServer::Message>> received_messsage;
			while (receivedMessageQueue.TryDequeue(received_messsage))
			{
				auto peers_iterator(peers.find(received_messsage.first));
				if (peers_iterator != peers.end())
				{
					try
					{
						std::shared_ptr<WhackAStoodentServer::Peer> peer(peers_iterator->second);
						WhackAStoodentServer::EMessageType message_type(received_messsage.second->GetMessageType());
						auto message_parser_list_iterator(messageParserLists.find(message_type));
						if (message_parser_list_iterator == messageParserLists.end())
						{
							peer->OnUnsupportedMessageTypeReceived(message_type);
							peer->SendPeerMessage<Messages::ErrorMessage>(EErrorType::UnsupportedMessageType, L"Unsupported message type \"" + std::to_wstring(static_cast<int>(message_type)) + L"\" has been received.");
						}
						else
						{
							peer->OnMessageReceived(received_messsage.second);
							for (const auto& message_parser : message_parser_list_iterator->second)
							{
								message_parser->ParsePeerMessage(peer, received_messsage.second);
							}
						}
					}
					catch (const std::exception& e)
					{
						std::cerr << e.what() << std::endl;
					}
				}
			}
		}
		lobby.ProcessTick();
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

/// <summary>
/// Networking thread
/// </summary>
/// <param name="server">Server</param>
void WhackAStoodentServer::Server::NetworkingThread(Server* server)
{
	ENetAddress enet_address;
	enet_address_set_hostname(&enet_address, "localhost");
	enet_address.port = server->port;
	server->enetHost = enet_host_create
	(
		&enet_address,
		static_cast<std::size_t>(ENET_PROTOCOL_MAXIMUM_PEER_ID),
		static_cast<std::size_t>(ENET_PROTOCOL_MAXIMUM_CHANNEL_COUNT),
		static_cast<std::uint32_t>(0),
		static_cast<std::uint32_t>(0),
		ENET_HOST_BUFFER_SIZE_MAX
	);
	if (server->enetHost)
	{
		ENetEvent enet_event;
		std::pair<std::shared_ptr<WhackAStoodentServer::Peer>, std::shared_ptr<WhackAStoodentServer::Message>> outgoing_message;
		bool is_polling;
		while (server->isNetworkingThreadRunning)
		{
			while (server->outgoingMessages.TryDequeue(outgoing_message))
			{
				ENetPacket* packet(enet_packet_create(outgoing_message.second->GetData().data(), outgoing_message.second->GetData().size(), ENET_PACKET_FLAG_RELIABLE));
				int error_code(enet_peer_send(outgoing_message.first->GetPeer(), 0, packet));
				if (error_code)
				{
					throw WhackAStoodentServer::ENetPeerSendFailedException(outgoing_message.first.get(), error_code);
				}
			}
			is_polling = true;
			while (is_polling)
			{
				int host_service_result(enet_host_service(server->enetHost, &enet_event, server->timeoutTime));
				is_polling = (host_service_result > 0);
				if (is_polling)
				{
					switch (enet_event.type)
					{
					case ENET_EVENT_TYPE_NONE:
						// ...
						break;
					case ENET_EVENT_TYPE_CONNECT:
						server->connectedPeerQueue.Enqueue(enet_event.peer);
						break;
					case ENET_EVENT_TYPE_DISCONNECT:
					case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
						server->disconnectedPeerQueue.Enqueue(enet_event.peer->incomingPeerID);
						break;
					case ENET_EVENT_TYPE_RECEIVE:
						server->receivedMessageQueue.Enqueue(std::make_pair(enet_event.peer->incomingPeerID, std::make_shared<WhackAStoodentServer::Message>(std::span<const std::uint8_t>(enet_event.packet->data, enet_event.packet->dataLength))));
						enet_packet_destroy(enet_event.packet);
						break;
					default:
						std::cerr << "Invalid ENet event type \"" << enet_event.type << "\"" << std::endl;
						break;
					}
				}
				else if (host_service_result < 0)
				{
					server->isNetworkingThreadRunning = false;
					std::cerr << "Failed to poll events from ENet." << std::endl;
				}
			}
		}
		enet_host_destroy(server->enetHost);
		server->enetHost = nullptr;
	}
	server->isNetworkingThreadRunning = false;
}

/// <summary>
/// Handles message parse failed event
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="message">Message</param>
void WhackAStoodentServer::Server::HandleMessageParseFailedEvent(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::Message> message)
{
	peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::MalformedMessage, L"Failed to parse message type \"" + std::to_wstring(static_cast<int>(message->GetMessageType())) + L"\"");
}

/// <summary>
/// Asserts that peer is authenticated
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="onPeerIsAuthenticated">USed to invoke when peer is authenticated</param>
void WhackAStoodentServer::Server::AssertPeerIsAuthenticated(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user)> onPeerIsAuthenticated)
{
	std::shared_ptr<WhackAStoodentServer::User> user;
	if (lobby.TryGetUserFromPeer(peer, user))
	{
		onPeerIsAuthenticated(user);
	}
	else
	{
		peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are not authenticated.");
	}
}

/// <summary>
/// Asserts that peer is authenticated and is not in game
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="onPeerIsAuthenticatedAndNotInGame">Used to invoke when peer is authenticated as is in game</param>
void WhackAStoodentServer::Server::AssertPeerIsAuthenticatedAndNotInGame(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user)> onPeerIsAuthenticatedAndNotInGame)
{
	AssertPeerIsAuthenticated
	(
		peer,
		[&](std::shared_ptr<WhackAStoodentServer::User> user)
		{
			if (lobby.IsUserInAGame(user))
			{
				peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are already in a game.");
			}
			else
			{
				onPeerIsAuthenticatedAndNotInGame(user);
			}
		}
	);
}

/// <summary>
/// Asserts that peer is in game
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="onPeerIsInGame">Used to invoke when peer is in game</param>
void WhackAStoodentServer::Server::AssertPeerIsInGame(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)> onPeerIsInGame)
{
	AssertPeerIsAuthenticated
	(
		peer,
		[&](std::shared_ptr<WhackAStoodentServer::User> user)
		{
			std::shared_ptr<WhackAStoodentServer::Game> game;
			if (lobby.TryGetUserGame(user, game))
			{
				onPeerIsInGame(user, game);
			}
			else
			{
				peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are not in a game.");
			}
		}
	);
}

/// <summary>
/// Asserts that peer is a hitter
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="onPeerIsAHitter">Used to invoke when peer is a hitter</param>
void WhackAStoodentServer::Server::AssertPeerIsAHitter(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)> onPeerIsAHitter)
{
	AssertPeerIsInGame
	(
		peer,
		[&](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
		{
			if (game->GetPlayerRole(user) == WhackAStoodentServer::EPlayerRole::Hitter)
			{
				onPeerIsAHitter(user, game);
			}
			else
			{
				peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are not a hitter.");
			}
		}
	);
}

/// <summary>
/// Asserts that peer is a mole
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="onPeerIsAMole">Used to invoke when peer is a mole</param>
void WhackAStoodentServer::Server::AssertPeerIsAMole(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::function<void(std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)> onPeerIsAMole)
{
	AssertPeerIsInGame
	(
		peer,
		[&](std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game> game)
		{
			if (game->GetPlayerRole(user) == WhackAStoodentServer::EPlayerRole::Mole)
			{
				onPeerIsAMole(user, game);
			}
			else
			{
				peer->SendPeerMessage<Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You are not a mole.");
			}
		}
	);
}
