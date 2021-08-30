#pragma once

#include <Abstract/ASerializableMessage.hpp>

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
		/// A class that describes a score mole message
		/// </summary>
		class ScoreMoleMessage : public ASerializableMessage<EMessageType::ScoreMole>
		{
		public:

			/// <summary>
			/// Constructs a score mole message
			/// </summary>
			ScoreMoleMessage();

			/// <summary>
			/// Constructs a score mole message
			/// </summary>
			/// <param name="points">Points</param>
			ScoreMoleMessage(std::int64_t points);

			/// <summary>
			/// Destroys score mole message
			/// </summary>
			virtual ~ScoreMoleMessage() override;

			/// <summary>
			/// Gets the points
			/// </summary>
			/// <returns>Points</returns>
			virtual std::int64_t GetPoints() const;

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
			/// Points
			/// </summary>
			std::int64_t points;
		};
	}
}
