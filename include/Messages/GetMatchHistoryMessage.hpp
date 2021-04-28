#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class GetMatchHistoryMessage : public ASerializableMessage<EMessageType::GetMatchHistory>
		{
		public:

			GetMatchHistoryMessage();

			virtual ~GetMatchHistoryMessage() override;
		};
	}
}
