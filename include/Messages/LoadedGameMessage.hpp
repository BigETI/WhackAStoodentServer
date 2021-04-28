#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class LoadedGameMessage : public ASerializableMessage<EMessageType::LoadedGame>
		{
		public:

			LoadedGameMessage();

			virtual ~LoadedGameMessage();
		};
	}
}
