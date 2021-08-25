#include <string>

#include <Exceptions/ENetPeerSendFailedException.hpp>

/// <summary>
/// Constructs an ENet peer send failed exception
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="errorCode">Error code</param>
WhackAStoodentServer::ENetPeerSendFailedException::ENetPeerSendFailedException(Peer* peer, int errorCode) :
	std::runtime_error("Failed to send message to peer. Error code: " + std::to_string(errorCode)),
	peer(peer),
	errorCode(errorCode)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
}

/// <summary>
/// Detroys ENet peer send failed exception
/// </summary>
WhackAStoodentServer::ENetPeerSendFailedException::~ENetPeerSendFailedException()
{
	// ...
}

/// <summary>
/// Gets the peer
/// </summary>
/// <returns>Peer</returns>
const WhackAStoodentServer::Peer& WhackAStoodentServer::ENetPeerSendFailedException::GetPeer() const
{
	return *peer;
}

/// <summary>
/// Gets the peer
/// </summary>
/// <returns>Peer</returns>
WhackAStoodentServer::Peer& WhackAStoodentServer::ENetPeerSendFailedException::GetPeer()
{
	return *peer;
}

/// <summary>
/// Gets the error code
/// </summary>
/// <returns>Error code</returns>
int WhackAStoodentServer::ENetPeerSendFailedException::GetErrorCode() const
{
	return errorCode;
}
