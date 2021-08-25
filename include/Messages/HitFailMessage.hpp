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
		/// A class that describes a hit fail message
		/// </summary>
		class HitFailMessage : public ASerializableMessage<EMessageType::HitFail>
		{
		public:

			/// <summary>
			/// Constructs a hit fail message
			/// </summary>
			HitFailMessage();

			/// <summary>
			/// Constructs a hit fail message
			/// </summary>
			/// <param name="position">Position</param>
			HitFailMessage(const Vector2D<float>& position);

			/// <summary>
			/// Destroys hit fail message
			/// </summary>
			virtual ~HitFailMessage() override;

			/// <summary>
			/// Gets the position
			/// </summary>
			/// <returns>Position</returns>
			virtual const Vector2D<float>& GetPosition() const;

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
			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			/// <summary>
			/// Position
			/// </summary>
			Vector2D<float> position;
		};
	}
}
