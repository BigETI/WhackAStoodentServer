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
	WhackAStoodentServer::IPUtilities::GetIPv4AddressString(peer->address.host, ipv4AddressString);
}

/// <summary>
/// Destructs peer
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
/// Gets the IPv4 address
/// </summary>
/// <returns>IPv4 address</returns>
std::uint32_t WhackAStoodentServer::Peer::GetIPv4Address() const
{
	return peer->address.host;
}

/// <summary>
/// Gets the IPv4 address string
/// </summary>
/// <returns>IPv4 address string</returns>
std::string_view WhackAStoodentServer::Peer::GetIPv4AddressString() const
{
	return ipv4AddressString;
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
