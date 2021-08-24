#pragma once

#include <memory>
#include <type_traits>
#include <functional>
#include <stdexcept>

#include <Interfaces/IMessageParser.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Misc/Message.hpp>
#include <Misc/Peer.hpp>

namespace WhackAStoodentServer
{
	template <typename T>
	class MessageParser : public IMessageParser
	{
	public:

		static_assert(std::is_base_of<ISerializableMessage, T>::value);

		using MessageType = T;

		MessageParser() = delete;
		MessageParser(const MessageParser<T>&) = delete;
		MessageParser(MessageParser<T>&&) = delete;

		MessageParser(std::function<void(std::shared_ptr<Peer> peer, const T& message)> onPeerMessageParsed, std::function<void(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message)> onPeerMessageParseFailed) :
			onPeerMessageParsed(onPeerMessageParsed),
			onPeerMessageParseFailed(onPeerMessageParseFailed)
		{
			if (!onPeerMessageParsed)
			{
				throw std::invalid_argument("Parameter \"onPeerMessageParsed\" is null.");
			}
		}

		virtual ~MessageParser()
		{
			// ...
		}

		virtual void ParsePeerMessage(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message) override
		{
			if (!peer)
			{
				throw std::invalid_argument("Parameter \"peer\" is null.");
			}
			if (!message)
			{
				throw std::invalid_argument("Parameter \"message\" is null.");
			}
			if (message->GetMessageType() == T::MessageType)
			{
				T message_data;
				if (message->TryGetData<T>(message_data))
				{
					onPeerMessageParsed(peer, message_data);
				}
				else
				{
					onPeerMessageParseFailed(peer, message);
				}
			}
			else
			{
				onPeerMessageParseFailed(peer, message);
			}
		}

		MessageParser<T>& operator=(const MessageParser<T>&) = delete;
		MessageParser<T>& operator=(MessageParser<T>&&) = delete;

	private:

		std::function<void(std::shared_ptr<Peer> peer, const T& message)> onPeerMessageParsed;

		std::function<void(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message)> onPeerMessageParseFailed;
	};
}
