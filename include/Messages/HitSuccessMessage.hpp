#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/ELookHole.hpp>
#include <Misc/Vector2D.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class HitSuccessMessage : public ASerializableMessage<EMessageType::HitSuccess>
		{
		public:

			HitSuccessMessage();

			HitSuccessMessage(ELookHole lookHole, std::int64_t points, const Vector2D<float>& position);

			virtual ~HitSuccessMessage();

			virtual ELookHole GetLookHole() const;

			virtual std::int64_t GetPoints() const;

			virtual const Vector2D<float>& GetPosition() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			ELookHole lookHole;

			std::int64_t points;

			Vector2D<float> position;
		};
	}
}
