#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include <Enumerators/EPlayerRole.hpp>
#include <Interfaces/ISerializable.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a match history entry
	/// </summary>
	class MatchHistoryEntry : ISerializable
	{
	public:

		/// <summary>
		/// Constructs a match history entry
		/// </summary>
		MatchHistoryEntry();

		/// <summary>
		/// Constructs a match history entry
		/// </summary>
		/// <param name="matchHistoryEntry">Match history entry</param>
		MatchHistoryEntry(const MatchHistoryEntry& matchHistoryEntry);

		/// <summary>
		/// Constructs a match history entry
		/// </summary>
		/// <param name="matchHistoryEntry">Match history entry</param>
		MatchHistoryEntry(MatchHistoryEntry&& matchHistoryEntry);

		/// <summary>
		/// Constructs a match history entry
		/// </summary>
		/// <param name="yourScore">Your score</param>
		/// <param name="yourRole">Your role</param>
		/// <param name="yourName">Your name</param>
		/// <param name="opponentScore">Opponent's score</param>
		/// <param name="opponentRole">Opponent's role</param>
		/// <param name="opponentName">Opponent's name</param>
		MatchHistoryEntry(std::int64_t yourScore, EPlayerRole yourRole, std::wstring_view yourName, std::int64_t opponentScore, EPlayerRole opponentRole, std::wstring_view opponentName);

		/// <summary>
		/// Destroys match history entry
		/// </summary>
		virtual ~MatchHistoryEntry();

		/// <summary>
		/// Gets your score
		/// </summary>
		/// <returns>Your score</returns>
		virtual std::int64_t GetYourScore() const;

		/// <summary>
		/// Gets your role
		/// </summary>
		/// <returns>Your role</returns>
		virtual WhackAStoodentServer::EPlayerRole GetYourRole() const;

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
		/// Gets opponent's role
		/// </summary>
		/// <returns>Opponent's role</returns>
		virtual WhackAStoodentServer::EPlayerRole GetOpponentRole() const;

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

		/// <summary>
		/// Assigns a match history entry to this object
		/// </summary>
		/// <param name="matchHistoryEntry">Match history entry</param>
		/// <returns>This object</returns>
		virtual MatchHistoryEntry& operator=(const MatchHistoryEntry& matchHistoryEntry);

		/// <summary>
		/// Assigns a match history entry to this object
		/// </summary>
		/// <param name="matchHistoryEntry">Match history entry</param>
		/// <returns>This object</returns>
		virtual MatchHistoryEntry& operator=(MatchHistoryEntry&& matchHistoryEntry) noexcept;

	private:

		/// <summary>
		/// Your score
		/// </summary>
		std::int64_t yourScore;

		/// <summary>
		/// Your role
		/// </summary>
		WhackAStoodentServer::EPlayerRole yourRole;

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
		WhackAStoodentServer::EPlayerRole opponentRole;

		/// <summary>
		/// Opponent's name
		/// </summary>
		std::wstring opponentName;
	};
}
