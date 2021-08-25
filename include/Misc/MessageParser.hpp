#pragma once

#include <memory>
#include <type_traits>
#include <functional>
#include <stdexcept>

#include <Interfaces/IMessageParser.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Misc/Message.hpp>
#include <Misc/Peer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a message parser
	/// </summary>
	/// <typeparam name="T">Message type</typeparam>
	template <typename T>
	class MessageParser : public IMessageParser
	{
	public:

		static_assert(std::is_base_of<ISerializableMessage, T>::value);

		/// <summary>
		/// Message type
		/// </summary>
		using MessageType = T;

		MessageParser() = delete;
		MessageParser(const MessageParser<T>&) = delete;
		MessageParser(MessageParser<T>&&) = delete;

		/// <summary>
		/// Constructs a new message parser
		/// </summary>
		/// <param name="onPeerMessageParsed">Used to invoke when peer message has been succesfully parsed</param>
		/// <param name="onPeerMessageParseFailed">Used to invoke when parsing peer message has failed</param>
		MessageParser(std::function<void(std::shared_ptr<Peer> peer, const T& message)> onPeerMessageParsed, std::function<void(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message)> onPeerMessageParseFailed) :
			onPeerMessageParsed(onPeerMessageParsed),
			onPeerMessageParseFailed(onPeerMessageParseFailed)
		{
			if (!onPeerMessageParsed)
			{
				throw std::invalid_argument("Parameter \"onPeerMessageParsed\" is null.");
			}
		}

		/// <summary>
		/// Destroys message parser
		/// </summary>
		virtual ~MessageParser()
		{
			// ...
		}

		/// <summary>
		/// Parses peer message
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="message">Message</param>
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

		/// <summary>
		/// Used to invoke when peer message has been succesfully parsed
		/// </summary>
		std::function<void(std::shared_ptr<Peer> peer, const T& message)> onPeerMessageParsed;

		/// <summary>
		/// Used to invoke when parsing peer message has failed
		/// </summary>
		std::function<void(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message)> onPeerMessageParseFailed;
	};
}
