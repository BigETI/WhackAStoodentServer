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
		/// A class that describes a started game message
		/// </summary>
		class StartedGameMessage : public ASerializableMessage<EMessageType::StartedGame>
		{
		public:

			/// <summary>
			/// Constructs a started game message
			/// </summary>
			StartedGameMessage();

			/// <summary>
			/// Constructs a started game message
			/// </summary>
			/// <param name="opponentSessionCode">Opponent's session code</param>
			/// <param name="opponentName">Opponent's name</param>
			StartedGameMessage(EPlayerRole yourRole, std::wstring_view opponentName);

			/// <summary>
			/// Destroys started game message
			/// </summary>
			virtual ~StartedGameMessage() override;

			/// <summary>
			/// Gets your role
			/// </summary>
			/// <returns>Your role</returns>
			virtual EPlayerRole GetYourRole() const;

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
			virtual nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Your role
			/// </summary>
			EPlayerRole yourRole;

			/// <summary>
			/// Opponent's name
			/// </summary>
			std::wstring opponentName;
		};
	}
}
