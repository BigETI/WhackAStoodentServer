#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class DenyAuthentificationMessage : public ASerializableMessage<EMessageType::DenyAuthentification>
		{
		public:

			DenyAuthentificationMessage();

			virtual ~DenyAuthentificationMessage();
		};
	}
}
