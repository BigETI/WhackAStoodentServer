#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <enet/enet.h>

#include <Enumerators/EDisconnectionReason.hpp>
#include <Enumerators/EErrorType.hpp>
#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Misc/Event.hpp>
#include <Misc/Message.hpp>

namespace WhackAStoodentServer
{
	class Peer
	{
	public:

		Event<> OnConnectionAttempted;

		Event<> OnConnected;

		Event<> OnDisconnected;

		Event<EMessageType> OnUnsupportedMessageTypeReceived;

		Event<std::shared_ptr<Message>> OnMessageReceived;

		Event<EErrorType, const std::wstring&> OnErrorReceived;

		Peer() = delete;
		Peer(const Peer&) = delete;
		Peer(Peer&&) = delete;

		Peer(ENetPeer* peer);

		virtual ~Peer();

		virtual std::uint16_t GetIncomingID() const;

		virtual std::uint16_t GetOutgoingID() const;

		template <typename T, typename... TArguments>
		void SendPeerMessage(TArguments... arguments)
		{
			static_assert(std::is_base_of<ISerializableMessage, T>::value);
			T message(arguments...);
			std::vector<std::uint8_t> data;
			SendPeerMessage(message.Serialize(data));
		}

		virtual void SendPeerMessage(const std::vector<uint8_t>& data);

		virtual void Disconnect(EDisconnectionReason reason);

		Peer& operator=(const Peer&) = delete;
		Peer& operator=(Peer&&) = delete;

	private:

		ENetPeer* peer;
	};
}
