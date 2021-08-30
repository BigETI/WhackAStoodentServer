#pragma once

#include <string>
#include <string_view>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EDenyPlayRequestReason.hpp>

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
		/// A class that describes a deny play request message
		/// </summary>
		class DenyPlayRequestMessage : public ASerializableMessage<EMessageType::DenyPlayRequest>
		{
		public:

			/// <summary>
			/// Constructs a deny play request message
			/// </summary>
			DenyPlayRequestMessage();

			/// <summary>
			/// Constructs a deny play request message
			/// </summary>
			/// <param name="reason">Reason</param>
			DenyPlayRequestMessage(EDenyPlayRequestReason reason);

			/// <summary>
			/// Destroys deny play request message
			/// </summary>
			virtual ~DenyPlayRequestMessage() override;

			/// <summary>
			/// Gets the deny play request reason
			/// </summary>
			/// <returns>Deny play request reason</returns>
			virtual EDenyPlayRequestReason GetReason() const;

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
			/// Deny play request reason
			/// </summary>
			EDenyPlayRequestReason reason;
		};
	}
}
