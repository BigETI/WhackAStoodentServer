#include <stdexcept>

#include <Exceptions/ENetPeerSendFailedException.hpp>
#include <Misc/Peer.hpp>

WhackAStoodentServer::Peer::Peer(ENetPeer* peer) : peer(peer)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
}

WhackAStoodentServer::Peer::~Peer()
{
	// ...
}

std::uint16_t WhackAStoodentServer::Peer::GetIncomingID() const
{
	return peer->incomingPeerID;
}

std::uint16_t WhackAStoodentServer::Peer::GetOutgoingID() const
{
	return peer->outgoingPeerID;
}

void WhackAStoodentServer::Peer::SendPeerMessage(const std::vector<uint8_t>& data)
{
	ENetPacket* packet(enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE));
	int error_code(enet_peer_send(peer, 0, packet));
	if (error_code)
	{
		throw ENetPeerSendFailedException(this, error_code);
	}
}

void WhackAStoodentServer::Peer::Disconnect(WhackAStoodentServer::EDisconnectionReason reason)
{
	enet_uint32 data(static_cast<enet_uint32>(reason));
	switch (reason)
	{
	case EDisconnectionReason::None:
		enet_peer_disconnect(peer, data);
		break;
	case EDisconnectionReason::Kicked:
	case EDisconnectionReason::Banned:
	case EDisconnectionReason::Stopped:
		enet_peer_disconnect_now(peer, data);
		break;
	}
}
