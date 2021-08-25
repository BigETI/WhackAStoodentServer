#pragma once

#include <stdexcept>

#include <Misc/Peer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an ENet peer send failed exception
	/// </summary>
	class ENetPeerSendFailedException : public std::runtime_error
	{
	public:

		ENetPeerSendFailedException() = delete;

		/// <summary>
		/// Constructs an ENet peer send failed exception
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="errorCode">Error code</param>
		ENetPeerSendFailedException(Peer* peer, int errorCode);

		/// <summary>
		/// Detroys ENet peer send failed exception
		/// </summary>
		virtual ~ENetPeerSendFailedException() override;

		/// <summary>
		/// Gets the peer
		/// </summary>
		/// <returns>Peer</returns>
		const Peer& GetPeer() const;

		/// <summary>
		/// Gets the peer
		/// </summary>
		/// <returns>Peer</returns>
		Peer& GetPeer();

		/// <summary>
		/// Gets the error code
		/// </summary>
		/// <returns>Error code</returns>
		int GetErrorCode() const;

	private:

		/// <summary>
		/// Peer
		/// </summary>
		Peer* peer;

		/// <summary>
		/// Error code
		/// </summary>
		int errorCode;
	};
}
