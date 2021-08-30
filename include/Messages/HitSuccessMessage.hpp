#pragma once

#include <cstdint>

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
		/// A class that 
		/// </summary>
		class HitSuccessMessage : public ASerializableMessage<EMessageType::HitSuccess>
		{
		public:

			/// <summary>
			/// Constructs a hit message
			/// </summary>
			HitSuccessMessage();

			/// <summary>
			/// Constructs a hit message
			/// </summary>
			/// <param name="lookHole">Look hole</param>
			/// <param name="points">Points</param>
			/// <param name="position">Position</param>
			HitSuccessMessage(std::size_t lookHole, std::int64_t points, const Vector2D<float>& position);

			/// <summary>
			/// Destroys hit message
			/// </summary>
			virtual ~HitSuccessMessage() override;

			/// <summary>
			/// Gets the look hole
			/// </summary>
			/// <returns>Look hole</returns>
			virtual std::size_t GetLookHole() const;

			/// <summary>
			/// Gets the points
			/// </summary>
			/// <returns>Points</returns>
			virtual std::int64_t GetPoints() const;

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
			virtual std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Look hole
			/// </summary>
			std::size_t lookHole;

			/// <summary>
			/// Points
			/// </summary>
			std::int64_t points;

			/// <summary>
			/// Position
			/// </summary>
			Vector2D<float> position;
		};
	}
}
