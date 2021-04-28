#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EDenyPlayRequestReason.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class DenyPlayRequestMessage : public ASerializableMessage<EMessageType::DenyPlayRequest>
		{
		public:

			DenyPlayRequestMessage();

			DenyPlayRequestMessage(EDenyPlayRequestReason reason);

			virtual ~DenyPlayRequestMessage();

			virtual EDenyPlayRequestReason GetReason() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			EDenyPlayRequestReason reason;
		};
	}
}
