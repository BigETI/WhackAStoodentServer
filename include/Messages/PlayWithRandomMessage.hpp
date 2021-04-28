#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class PlayWithRandomMessage : public ASerializableMessage<EMessageType::PlayWithRandom>
		{
		public:

			PlayWithRandomMessage();

			virtual ~PlayWithRandomMessage() override;
		};
	}
}
