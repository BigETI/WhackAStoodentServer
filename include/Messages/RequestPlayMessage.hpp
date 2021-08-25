#pragma once

#include <string>
#include <string_view>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EPlayerRole.hpp>

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
			/// <param name="playerRole">Player role</param>
			/// <param name="opponentName">Opponent name</param>
			RequestPlayMessage(EPlayerRole playerRole, std::wstring_view opponentName);

			/// <summary>
			/// Destroys request play message
			/// </summary>
			virtual ~RequestPlayMessage() override;

			/// <summary>
			/// Gets the player role
			/// </summary>
			/// <returns>Player role</returns>
			virtual EPlayerRole GetPlayerRole() const;

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
			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			/// <summary>
			/// Player role
			/// </summary>
			EPlayerRole playerRole;
			
			/// <summary>
			/// Opponent's name
			/// </summary>
			std::wstring opponentName;
		};
	}
}
