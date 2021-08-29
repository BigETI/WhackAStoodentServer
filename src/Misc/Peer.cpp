#include <stdexcept>

#include <Exceptions/ENetPeerSendFailedException.hpp>
#include <Misc/Peer.hpp>
#include <Static/IPUtilities.hpp>

/// <summary>
/// Constructs a new peer
/// </summary>
/// <param name="peer">ENet peer</param>
WhackAStoodentServer::Peer::Peer(ENetPeer* peer) : peer(peer)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
	WhackAStoodentServer::IPUtilities::GetIPAddressString(peer->address, ipAddressString);
}

/// <summary>
/// Destroys peer
/// </summary>
WhackAStoodentServer::Peer::~Peer()
{
	// ...
}

/// <summary>
/// Gets the incoming peer ID
/// </summary>
/// <returns>Incoming peer ID</returns>
std::uint16_t WhackAStoodentServer::Peer::GetIncomingPeerID() const
{
	return peer->incomingPeerID;
}

/// <summary>
/// Gets the outgoing peer ID
/// </summary>
/// <returns>Outgoing peer ID</returns>
std::uint16_t WhackAStoodentServer::Peer::GetOutgoingPeerID() const
{
	return peer->outgoingPeerID;
}

/// <summary>
/// Gets the IP address string
/// </summary>
/// <returns>IP address string</returns>
std::string_view WhackAStoodentServer::Peer::GetIPAddressString() const
{
	return ipAddressString;
}

/// <summary>
/// Sends a peer message
/// </summary>
/// <param name="data">Data</param>
void WhackAStoodentServer::Peer::SendPeerMessage(const std::vector<uint8_t>& data)
{
	ENetPacket* packet(enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE));
	int error_code(enet_peer_send(peer, 0, packet));
	if (error_code)
	{
		throw ENetPeerSendFailedException(this, error_code);
	}
}

/// <summary>
/// Disconnects peer
/// </summary>
/// <param name="reason">Disconnection reason</param>
void WhackAStoodentServer::Peer::Disconnect(WhackAStoodentServer::EDisconnectionReason reason)
{
	std::uint32_t data(static_cast<std::uint32_t>(reason));
	switch (reason)
	{
	case EDisconnectionReason::NoReason:
		enet_peer_disconnect(peer, data);
		break;
	case EDisconnectionReason::Kicked:
	case EDisconnectionReason::Banned:
	case EDisconnectionReason::Stopped:
		enet_peer_disconnect_now(peer, data);
		break;
	}
}
