#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class AcceptPlayRequestMessage : public ASerializableMessage<EMessageType::AcceptPlayRequest>
		{
		public:

			AcceptPlayRequestMessage();

			virtual ~AcceptPlayRequestMessage();
		};
	}
}
