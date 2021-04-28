#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class HideMessage : public ASerializableMessage<EMessageType::Hide>
		{
		public:

			HideMessage();

			virtual ~HideMessage();
		};
	}
}
