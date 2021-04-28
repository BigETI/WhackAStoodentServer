#include <string>

#include <Exceptions/ENetPeerSendFailedException.hpp>

WhackAStoodentServer::ENetPeerSendFailedException::ENetPeerSendFailedException(Peer* peer, int errorCode) :
	std::runtime_error("Failed to send message to peer. Error code: " + std::to_string(errorCode)),
	peer(peer),
	errorCode(errorCode)
{
	if (!peer)
	{
		throw std::invalid_argument("\"peer\" is null.");
	}
}

WhackAStoodentServer::ENetPeerSendFailedException::~ENetPeerSendFailedException()
{
	// ...
}

const WhackAStoodentServer::Peer& WhackAStoodentServer::ENetPeerSendFailedException::GetPeer() const
{
	return *peer;
}

WhackAStoodentServer::Peer& WhackAStoodentServer::ENetPeerSendFailedException::GetPeer()
{
	return *peer;
}

int WhackAStoodentServer::ENetPeerSendFailedException::GetErrorCode() const
{
	return errorCode;
}
