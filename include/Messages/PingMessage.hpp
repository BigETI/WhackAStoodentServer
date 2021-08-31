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
		/// A class that describes a ping message
		/// </summary>
		class PingMessage : public ASerializableMessage<EMessageType::Ping>
		{
		public:

			/// <summary>
			/// Constructs a ping message
			/// </summary>
			PingMessage();

			/// <summary>
			/// Constructs a ping message
			/// </summary>
			/// <param name="pingData">Ping data</param>
			PingMessage(std::int32_t pingData);

			/// <summary>
			/// Destroys ping message
			/// </summary>
			virtual ~PingMessage() override;

			/// <summary>
			/// Gets the ping data
			/// </summary>
			/// <returns>Ping data</returns>
			virtual std::int32_t GetPingData() const;

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
			/// Ping data
			/// </summary>
			std::int32_t pingData;
		};
	}
}
