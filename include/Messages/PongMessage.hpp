#pragma once

#include <cstdint>

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class PongMessage : public ASerializableMessage<EMessageType::Pong>
		{
		public:

			PongMessage();

			PongMessage(int32_t pongData);

			virtual ~PongMessage() override;

			virtual std::int32_t GetPongData() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			std::int32_t pongData;
		};
	}
}
