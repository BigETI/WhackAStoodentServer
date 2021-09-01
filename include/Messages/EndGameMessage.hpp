#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <uuid.h>

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
		/// A class that describes an end game message
		/// </summary>
		class EndGameMessage : public ASerializableMessage<EMessageType::EndGame>
		{
		public:

			/// <summary>
			/// Constructs an end game message
			/// </summary>
			EndGameMessage();

			/// <summary>
			/// Constructs an end game message
			/// </summary>
			/// <param name="sessionID">Session ID</param>
			/// <param name="yourScore">Your score</param>
			/// <param name="yourRole">Your role</param>
			/// <param name="yourName">Your name</param>
			/// <param name="opponentScore">Opponent's score</param>
			/// <param name="opponentRole">Opponent's role</param>
			/// <param name="opponentName">Opponent's name</param>
			EndGameMessage(const uuids::uuid& sessionID, std::int64_t yourScore, EPlayerRole yourRole, std::wstring_view yourName, std::int64_t opponentScore, EPlayerRole opponentRole, std::wstring_view opponentName);

			/// <summary>
			/// Destroys end game message
			/// </summary>
			virtual ~EndGameMessage() override;

			/// <summary>
			/// Gets the session ID
			/// </summary>
			/// <param name="result">Result</param>
			/// <returns>Session ID</returns>
			virtual uuids::uuid& GetSessionID(uuids::uuid& result) const;

			/// <summary>
			/// Gets your score
			/// </summary>
			/// <returns>Your score</returns>
			virtual std::int64_t GetYourScore() const;

			/// <summary>
			/// Gets your role
			/// </summary>
			/// <returns>Your role</returns>
			virtual EPlayerRole GetYourRole() const;

			/// <summary>
			/// Gets your name
			/// </summary>
			/// <returns>Your name</returns>
			virtual std::wstring_view GetYourName() const;

			/// <summary>
			/// Gets the opponent's score
			/// </summary>
			/// <returns>Opponent's score</returns>
			virtual std::int64_t GetOpponentScore() const;

			/// <summary>
			/// Gets the opponent's role
			/// </summary>
			/// <returns>Opponent's role</returns>
			virtual EPlayerRole GetOpponentRole() const;

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
			/// Session ID
			/// </summary>
			uuids::uuid sessionID;

			/// <summary>
			/// Your score
			/// </summary>
			std::int64_t yourScore;

			/// <summary>
			/// Your role
			/// </summary>
			EPlayerRole yourRole;

			/// <summary>
			/// Your name
			/// </summary>
			std::wstring yourName;

			/// <summary>
			/// Opponent's score
			/// </summary>
			std::int64_t opponentScore;

			/// <summary>
			/// Opponent's role
			/// </summary>
			EPlayerRole opponentRole;

			/// <summary>
			/// Opponent's name
			/// </summary>
			std::wstring opponentName;
		};
	}
}
