#pragma once

#include <cstdint>
#include <vector>

#include <enet/enet.h>

#include <Enumerators/EDisconnectionReason.hpp>
#include <Interfaces/ISerializableMessage.hpp>

namespace WhackAStoodentServer
{
	class Peer
	{
	public:

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

	private:

		ENetPeer* peer;
	};
}
