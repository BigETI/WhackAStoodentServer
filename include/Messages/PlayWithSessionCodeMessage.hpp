#pragma once

#include <uuid.h>
#include <string>
#include <string_view>

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
		/// A class that describes a play with session code message
		/// </summary>
		class PlayWithSessionCodeMessage : public ASerializableMessage<EMessageType::PlayWithSessionCode>
		{
		public:

			/// <summary>
			/// Session code character count
			/// </summary>
			static constexpr const std::size_t SessionCodeCharacterCount = static_cast<const std::size_t>(6);

			/// <summary>
			/// Constructs a play with session code message
			/// </summary>
			PlayWithSessionCodeMessage();

			/// <summary>
			/// Constructs a play with session code message
			/// </summary>
			/// <param name="sessionCode">Session code</param>
			PlayWithSessionCodeMessage(std::string_view sessionCode);

			/// <summary>
			/// Destroys play with session code message
			/// </summary>
			virtual ~PlayWithSessionCodeMessage() override;

			/// <summary>
			/// Gets the session code
			/// </summary>
			/// <returns>Session code</returns>
			virtual std::string_view GetSessionCode() const;

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
			/// Session code
			/// </summary>
			std::string sessionCode;
		};
	}
}
