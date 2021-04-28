#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Misc/Vector2D.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class HitMessage : public ASerializableMessage<EMessageType::Hit>
		{
		public:

			HitMessage();

			HitMessage(const Vector2D<float>& position);

			const Vector2D<float>& GetPosition() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			Vector2D<float> position;
		};
	}
}
