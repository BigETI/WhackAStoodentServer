#pragma once

#include <cstdint>

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
		/// A class that describes a pong message
		/// </summary>
		class PongMessage : public ASerializableMessage<EMessageType::Pong>
		{
		public:

			/// <summary>
			/// Constructs a pong message
			/// </summary>
			PongMessage();

			/// <summary>
			/// Constructs a pong message
			/// </summary>
			/// <param name="pongData">Pong data</param>
			PongMessage(int32_t pongData);

			/// <summary>
			/// Destroys pong message
			/// </summary>
			virtual ~PongMessage() override;

			/// <summary>
			/// Gets the pong data
			/// </summary>
			/// <returns>Pong data</returns>
			virtual std::int32_t GetPongData() const;

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
			/// Pong data
			/// </summary>
			std::int32_t pongData;
		};
	}
}
