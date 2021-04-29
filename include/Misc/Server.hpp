#pragma once

#include <cstdint>
#include <forward_list>
#include <functional>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>

#include <enet/enet.h>
#include <uuid.h>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EErrorType.hpp>
#include <Misc/Event.hpp>
#include <Misc/Game.hpp>
#include <Misc/Message.hpp>
#include <Misc/MessageParser.hpp>
#include <Misc/User.hpp>

namespace WhackAStoodentServer
{
	class Server
	{
	public:

		Event<std::shared_ptr<Peer>> OnPeerConnectionAttempted;

		Event<std::shared_ptr<Peer>> OnPeerConnected;

		Event<std::shared_ptr<Peer>> OnPeerDisconnected;

		Event<std::shared_ptr<User>> OnUserConnected;

		Event<std::shared_ptr<User>> OnUserDisconnected;

		Server() = delete;
		Server(const Server&) = delete;
		Server(Server&&) = delete;

		Server(std::uint16_t port, std::uint32_t timeoutTime);

		virtual ~Server();

		virtual bool Start();

		virtual void Stop();

		virtual bool IsRunning() const;

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

		virtual bool ProcessMessages();

		Server& operator=(const Server&) = delete;
		Server& operator=(Server&&) = delete;

	private:

		std::uint16_t port;

		std::uint32_t timeoutTime;

		ENetHost* enetHost;

		std::unordered_map<std::uint16_t, std::shared_ptr<Peer>> peers;

		std::unordered_map<std::uint16_t, std::shared_ptr<User>> users;

		std::unordered_map<uuids::uuid, std::uint16_t> userIDToPeerIDLookup;

		std::unordered_map<EMessageType, std::forward_list<std::shared_ptr<IMessageParser>>> messageParserLists;

		virtual void HandleMessageParseFailedEvent(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message);

		virtual void AssertPeerIsAuthenticated(std::shared_ptr<Peer> peer, std::function<void(std::shared_ptr<User> user)> onPeerIsAuthenticated);

		virtual void AssertPeerIsInGame(std::shared_ptr<Peer>, std::function<void(std::shared_ptr<User> user, std::shared_ptr<Game> game)> onPeerIsInGame);
	};
}
