#pragma once

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class ScoreMoleMessage : public ASerializableMessage<EMessageType::ScoreMole>
		{
		public:

			ScoreMoleMessage();

			ScoreMoleMessage(std::int64_t points);

			virtual ~ScoreMoleMessage();

			virtual std::int64_t GetPoints() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			std::int64_t points;
		};
	}
}
