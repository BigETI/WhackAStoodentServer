#pragma once

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
		/// A class that describes a request play message
		/// </summary>
		class RequestPlayMessage : public ASerializableMessage<EMessageType::RequestPlay>
		{
		public:

			/// <summary>
			/// Constructs a request play message
			/// </summary>
			RequestPlayMessage();

			/// <summary>
			/// Constructs a request play message
			/// </summary>
			/// <param name="opponentSessionCode">Opponent's session code</param>
			/// <param name="opponentName">Opponent's name</param>
			RequestPlayMessage(std::string_view opponentSessionCode, std::wstring_view opponentName);

			/// <summary>
			/// Destroys request play message
			/// </summary>
			virtual ~RequestPlayMessage() override;

			/// <summary>
			/// Gets the opponent's session code
			/// </summary>
			/// <returns>Opponent's session code</returns>
			virtual std::string_view GetOpponentSessionCode() const;

			/// <summary>
			/// Gets the opponent's name
			/// </summary>
			/// <returns>Opponent's name</returns>
			virtual std::wstring_view GetOpponentName() const;

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
			/// Opponent's session code
			/// </summary>
			std::string opponentSessionCode;

			/// <summary>
			/// Opponent's name
			/// </summary>
			std::wstring opponentName;
		};
	}
}
