#pragma once

#include <cstdint>
#include <forward_list>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>

#include <enet.h>
#include <uuid.h>

#include <Abstract/ASerializableMessage.hpp>
#include <Misc/Bans.hpp>
#include <Misc/ConcurrentQueue.hpp>
#include <Misc/Event.hpp>
#include <Misc/Game.hpp>
#include <Misc/Lobby.hpp>
#include <Misc/Message.hpp>
#include <Misc/MessageParser.hpp>
#include <Misc/User.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a server
	/// </summary>
	class Server
	{
	public:

		/// <summary>
		/// Used to invoke when peer connection has been attempted
		/// </summary>
		Event<std::shared_ptr<Peer>> OnPeerConnectionAttempted;

		/// <summary>
		/// Used to invoke when peer has been connected
		/// </summary>
		Event<std::shared_ptr<Peer>> OnPeerConnected;

		/// <summary>
		/// Used to invoke when peer has been disconnected
		/// </summary>
		Event<std::shared_ptr<Peer>> OnPeerDisconnected;

		Server() = delete;
		Server(const Server&) = delete;
		Server(Server&&) = delete;

		/// <summary>
		/// Constructs a server
		/// </summary>
		/// <param name="port">Network port</param>
		/// <param name="timeoutTime">Timeout time</param>
		Server(std::uint16_t port, std::uint32_t timeoutTime);

		/// <summary>
		/// Destroys server
		/// </summary>
		virtual ~Server();

		/// <summary>
		/// Starts this server
		/// </summary>
		/// <returns>"true" if starting server was successful, otherwise "false"</returns>
		virtual bool Start();

		/// <summary>
		/// Stops this server
		/// </summary>
		virtual void Stop();

		/// <summary>
		/// Is this server running
		/// </summary>
		/// <returns>"true" if this server is running, otherwise "false"</returns>
		virtual bool IsRunning() const;

		/// <summary>
		/// Adds a new message parser
		/// </summary>
		/// <typeparam name="T">Message type</typeparam>
		/// <param name="onPeerMessageParsed">Used to invoke when message has been successfully parsed</param>
		/// <param name="onPeerMessageParseFailed">Used to invoke when parsing message has failed</param>
		template <typename T>
		void AddMessageParser(std::function<void(std::shared_ptr<Peer> peer, const T& message)> onPeerMessageParsed, std::function<void(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message)> onPeerMessageParseFailed)
		{
			static_assert(std::is_base_of<Messages::ASerializableMessage<T::MessageType>, T>::value);
			std::shared_ptr<IMessageParser> message_parser(std::make_shared<MessageParser<T>>(onPeerMessageParsed, onPeerMessageParseFailed));
			auto message_parser_list_iterator(messageParserLists.find(T::MessageType));
			if (message_parser_list_iterator == messageParserLists.end())
			{
				messageParserLists.insert_or_assign(T::MessageType, std::forward_list<std::shared_ptr<IMessageParser>>({ message_parser }));
			}
			else
			{
				message_parser_list_iterator->second.push_front(message_parser);
			}
		}

		/// <summary>
		/// Processes messages
		/// </summary>
		/// <returns>"true" if server is still running, otherwise "false"</returns>
		virtual bool ProcessMessages();

		/// <summary>
		/// Gets bans
		/// </summary>
		/// <returns>Bans</returns>
		virtual Bans& GetBans();

		/// <summary>
		/// Gets bans
		/// </summary>
		/// <returns>Bans</returns>
		virtual const Bans& GetBans() const;

		Server& operator=(const Server&) = delete;
		Server& operator=(Server&&) = delete;

	private:

		/// <summary>
		/// Network port
		/// </summary>
		std::uint16_t port;

		/// <summary>
		/// Timeout time
		/// </summary>
		std::uint32_t timeoutTime;

		/// <summary>
		/// ENet host
		/// </summary>
		ENetHost* enetHost;

		/// <summary>
		/// Networking thread
		/// </summary>
		std::thread* networkingThread;

		/// <summary>
		/// Is networking thread running
		/// </summary>
		volatile bool isNetworkingThreadRunning;

		/// <summary>
		/// Connected peer queue
		/// </summary>
		ConcurrentQueue<ENetPeer*> connectedPeerQueue;

		/// <summary>
		/// Disconnected peer queue
		/// </summary>
		ConcurrentQueue<std::uint16_t> disconnectedPeerQueue;

		/// <summary>
		/// Received message queue
		/// </summary>
		ConcurrentQueue<std::pair<std::uint16_t, std::shared_ptr<Message>>> receivedMessageQueue;

		/// <summary>
		/// Bans
		/// </summary>
		Bans bans;

		/// <summary>
		/// Lobby
		/// </summary>
		Lobby lobby;

		/// <summary>
		/// Peers
		/// </summary>
		std::unordered_map<std::uint16_t, std::shared_ptr<Peer>> peers;

		/// <summary>
		/// Message parser lists
		/// </summary>
		std::unordered_map<EMessageType, std::forward_list<std::shared_ptr<IMessageParser>>> messageParserLists;

		/// <summary>
		/// Outgoing messages
		/// </summary>
		ConcurrentQueue<std::pair<std::shared_ptr<Peer>, std::shared_ptr<Message>>> outgoingMessages;

		/// <summary>
		/// Networking thread
		/// </summary>
		/// <param name="server">Server</param>
		static void NetworkingThread(Server* server);

		/// <summary>
		/// Handles message parse failed event
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="message">Message</param>
		virtual void HandleMessageParseFailedEvent(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message);

		/// <summary>
		/// Asserts that peer is authenticated
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsAuthenticated">USed to invoke when peer is authenticated</param>
		virtual void AssertPeerIsAuthenticated(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user)> onPeerIsAuthenticated);

		/// <summary>
		/// Asserts that peer is authenticated and is not in game
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsAuthenticatedAndNotInGame">Used to invoke when peer is authenticated as is in game</param>
		virtual void AssertPeerIsAuthenticatedAndNotInGame(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user)> onPeerIsAuthenticatedAndNotInGame);

		/// <summary>
		/// Asserts that peer is in game
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsInGame">Used to invoke when peer is in game</param>
		virtual void AssertPeerIsInGame(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user, std::shared_ptr<Game> game)> onPeerIsInGame);

		/// <summary>
		/// Asserts that peer is a hitter
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsAHitter">Used to invoke when peer is a hitter</param>
		virtual void AssertPeerIsAHitter(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user, std::shared_ptr<Game> game)> onPeerIsAHitter);

		/// <summary>
		/// Asserts that peer is a mole
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsAMole">Used to invoke when peer is a mole</param>
		virtual void AssertPeerIsAMole(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user, std::shared_ptr<Game> game)> onPeerIsAMole);
	};
}
