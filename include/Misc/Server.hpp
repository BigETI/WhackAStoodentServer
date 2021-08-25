#pragma once

#include <cstdint>
#include <forward_list>
#include <functional>
#include <type_traits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <enet/enet.h>
#include <uuid.h>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EErrorType.hpp>
#include <Misc/Bans.hpp>
#include <Misc/Event.hpp>
#include <Misc/Game.hpp>
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

		/// <summary>
		/// Used to invoke when an user has connected
		/// </summary>
		Event<std::shared_ptr<User>> OnUserConnected;

		/// <summary>
		/// Used to invoke when an user has been disconnected
		/// </summary>
		Event<std::shared_ptr<User>> OnUserDisconnected;

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
		/// Bans
		/// </summary>
		Bans bans;

		/// <summary>
		/// Peers
		/// </summary>
		std::unordered_map<std::uint16_t, std::shared_ptr<Peer>> peers;

		/// <summary>
		/// Users
		/// </summary>
		std::unordered_map<std::uint16_t, std::shared_ptr<User>> users;

		/// <summary>
		/// Games
		/// </summary>
		std::unordered_map<uuids::uuid, std::shared_ptr<Game>> games;

		/// <summary>
		/// User ID to peer ID lookup
		/// </summary>
		std::unordered_map<uuids::uuid, std::uint16_t> userIDToPeerIDLookup;

		/// <summary>
		/// Session code to user ID lookup
		/// </summary>
		std::unordered_map<std::string, std::shared_ptr<User>> sessionCodeToUserIDLookup;

		/// <summary>
		/// Message parser lists
		/// </summary>
		std::unordered_map<EMessageType, std::forward_list<std::shared_ptr<IMessageParser>>> messageParserLists;

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
		/// Asserts that peer is in game
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="onPeerIsInGame">Used to invoke when peer in in game</param>
		virtual void AssertPeerIsInGame(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user, std::shared_ptr<Game> game)> onPeerIsInGame);
	};
}
