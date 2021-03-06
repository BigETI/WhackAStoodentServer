#pragma once

#include <cstddef>

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
		/// A class that describes a look message
		/// </summary>
		class LookMessage : public ASerializableMessage<EMessageType::Look>
		{
		public:

			/// <summary>
			/// Constructs a look message
			/// </summary>
			LookMessage();

			/// <summary>
			/// Constructs a look message
			/// </summary>
			/// <param name="lookHole">Look hole</param>
			LookMessage(std::size_t lookHole);

			/// <summary>
			/// Gets the look hole
			/// </summary>
			/// <returns>Look hole</returns>
			std::size_t GetLookHole() const;

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
			/// Look hole
			/// </summary>
			std::size_t lookHole;
		};
	}
}
