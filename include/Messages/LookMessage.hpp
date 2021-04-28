#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/ELookHole.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class LookMessage : public ASerializableMessage<EMessageType::Look>
		{
		public:

			LookMessage();

			LookMessage(ELookHole lookHole);

			ELookHole GetLookHole() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			ELookHole lookHole;
		};
	}
}
