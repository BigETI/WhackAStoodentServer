#pragma once

#include <cstdint>

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class PingMessage : public ASerializableMessage<EMessageType::Ping>
		{
		public:

			PingMessage();

			PingMessage(std::int32_t pingData);

			virtual ~PingMessage() override;

			virtual std::int32_t GetPingData() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			std::int32_t pingData;
		};
	}
}
