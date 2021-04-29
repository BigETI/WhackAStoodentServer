#pragma once

#include <memory>

#include <Misc/Message.hpp>
#include <Misc/Peer.hpp>

namespace WhackAStoodentServer
{
	class IMessageParser
	{
	public:

		virtual void ParsePeerMessage(std::shared_ptr<Peer> peer, std::shared_ptr<Message> message) = 0;
	};
}
