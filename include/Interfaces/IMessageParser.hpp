#pragma once

#include <memory>

#include <Misc/Message.hpp>
#include <Misc/Peer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// An interface that represents a message parser
	/// </summary>
	class IMessageParser
	{
	public:

		/// <summary>
		/// Parses peer message
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="message">Message</param>
		virtual void ParsePeerMessage(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message) = 0;
	};
}
