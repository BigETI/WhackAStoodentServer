#include <stdexcept>

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
/// Gets the ENet peer
/// </summary>
/// <returns>ENet peer</returns>
ENetPeer* WhackAStoodentServer::Peer::GetPeer() const
{
	return peer;
}

/// <summary>
/// Sends a peer message
/// </summary>
/// <param name="data">Data</param>
void WhackAStoodentServer::Peer::SendPeerMessage(nonstd::span<const std::uint8_t> data)
{
	OnMessageSent(std::make_shared<WhackAStoodentServer::Message>(data));
}

/// <summary>
/// Disconnects peer
/// </summary>
/// <param name="reason">Disconnection reason</param>
void WhackAStoodentServer::Peer::Disconnect(WhackAStoodentServer::EDisconnectionReason reason)
{
	// TODO: Enqueue this!
	std::uint32_t data(static_cast<std::uint32_t>(reason));
	switch (reason)
	{
	case WhackAStoodentServer::EDisconnectionReason::NoReason:
		enet_peer_disconnect(peer, data);
		break;
	case WhackAStoodentServer::EDisconnectionReason::Kicked:
	case WhackAStoodentServer::EDisconnectionReason::Banned:
	case WhackAStoodentServer::EDisconnectionReason::Stopped:
		enet_peer_disconnect_now(peer, data);
		break;
	}
}
