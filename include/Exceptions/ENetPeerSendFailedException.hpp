#pragma once

#include <stdexcept>

#include <Misc/Peer.hpp>

namespace WhackAStoodentServer
{
	class ENetPeerSendFailedException : public std::runtime_error
	{
	public:

		ENetPeerSendFailedException() = delete;

		ENetPeerSendFailedException(Peer* peer, int errorCode);

		virtual ~ENetPeerSendFailedException();

		const Peer& GetPeer() const;

		Peer& GetPeer();

		int GetErrorCode() const;

	private:

		Peer* peer;

		int errorCode;
	};
}
