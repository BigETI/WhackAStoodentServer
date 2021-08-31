#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Misc/Vector2D.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Whack-A-Stoodent server messages namespace
	/// </summary>
	namespace Messages
	{
		/// <summary>
		/// A class that describes a hit message
		/// </summary>
		class HitMessage : public ASerializableMessage<EMessageType::Hit>
		{
		public:

			/// <summary>
			/// Constructs a hit message
			/// </summary>
			HitMessage();

			/// <summary>
			/// Constructs a hit message
			/// </summary>
			/// <param name="position">Position</param>
			HitMessage(const Vector2D<float>& position);

			/// <summary>
			/// Destroys hit message
			/// </summary>
			virtual ~HitMessage() override;

			/// <summary>
			/// Gets the position
			/// </summary>
			/// <returns></returns>
			const Vector2D<float>& GetPosition() const;

			/// <summary>
			/// Serializes contents
			/// </summary>
			/// <param name="result">Result</param>
			/// <returns>Serialized contents</returns>
			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			/// <summary>
			/// Deserializes given input
			/// </summary>
			/// <param name="data">Data to deserialize</param>
			/// <returns>Remaining data to deserialize</returns>
			virtual nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Position
			/// </summary>
			Vector2D<float> position;
		};
	}
}
