#include <Misc/MatchHistoryEntry.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a match history entry
/// </summary>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry() :
	yourScore(static_cast<std::int64_t>(0)),
	opponentScore(static_cast<std::int64_t>(0))
{
	// ...
}

/// <summary>
/// Constructs a match history entry
/// </summary>
/// <param name="matchHistoryEntry">Match history entry</param>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(const WhackAStoodentServer::MatchHistoryEntry& matchHistoryEntry) :
	yourScore(matchHistoryEntry.yourScore),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentName(matchHistoryEntry.opponentName)
{
	// ...
}

/// <summary>
/// Constructs a match history entry
/// </summary>
/// <param name="matchHistoryEntry">Match history entry</param>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(WhackAStoodentServer::MatchHistoryEntry&& matchHistoryEntry) :
	yourScore(matchHistoryEntry.yourScore),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentName(matchHistoryEntry.opponentName)
{
	// ...
}

/// <summary>
/// Constructs a match history entry
/// </summary>
/// <param name="yourScore">Your score</param>
/// <param name="yourName">Your name</param>
/// <param name="opponentScore">Opponent's name</param>
/// <param name="opponentName">Opponent's name</param>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(std::int64_t yourScore, std::wstring_view yourName, std::int64_t opponentScore, std::wstring_view opponentName) :
	yourScore(yourScore),
	yourName(yourName),
	opponentScore(opponentScore),
	opponentName(opponentName)
{
	// ...
}

/// <summary>
/// Destroys match history entry
/// </summary>
WhackAStoodentServer::MatchHistoryEntry::~MatchHistoryEntry()
{
	// ...
}

/// <summary>
/// Gets your score
/// </summary>
/// <returns>Your score</returns>
std::int64_t WhackAStoodentServer::MatchHistoryEntry::GetYourScore() const
{
	return yourScore;
}

/// <summary>
/// Gets your name
/// </summary>
/// <returns>Your name</returns>
std::wstring_view WhackAStoodentServer::MatchHistoryEntry::GetYourName() const
{
	return yourName;
}

/// <summary>
/// Gets the opponent's score
/// </summary>
/// <returns>Opponent's score</returns>
std::int64_t WhackAStoodentServer::MatchHistoryEntry::GetOpponentScore() const
{
	return opponentScore;
}

/// <summary>
/// Gets the opponent's name
/// </summary>
/// <returns>Opponent's name</returns>
std::wstring_view WhackAStoodentServer::MatchHistoryEntry::GetOpponentName() const
{
	return opponentName;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::MatchHistoryEntry::Serialize(std::vector<std::uint8_t>& result) const
{
	NumericSerializer::SerializeLong(yourScore, result);
	StringSerializer::SerializeByteSizedString(yourName, result);
	NumericSerializer::SerializeLong(opponentScore, result);
	return StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::MatchHistoryEntry::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(NumericSerializer::DeserializeLong(data, yourScore));
	next_bytes = StringSerializer::DeserializeByteSizedString(next_bytes, yourName);
	next_bytes = NumericSerializer::DeserializeLong(next_bytes, opponentScore);
	return StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}

/// <summary>
/// Assigns a match history entry to this object
/// </summary>
/// <param name="matchHistoryEntry">Match history entry</param>
/// <returns>This object</returns>
WhackAStoodentServer::MatchHistoryEntry& WhackAStoodentServer::MatchHistoryEntry::operator=(const WhackAStoodentServer::MatchHistoryEntry& matchHistoryEntry)
{
	yourScore = matchHistoryEntry.yourScore;
	yourName = matchHistoryEntry.yourName;
	opponentScore = matchHistoryEntry.opponentScore;
	opponentName = matchHistoryEntry.opponentName;
	return *this;
}

/// <summary>
/// Assigns a match history entry to this object
/// </summary>
/// <param name="matchHistoryEntry">Match history entry</param>
/// <returns>This object</returns>
WhackAStoodentServer::MatchHistoryEntry& WhackAStoodentServer::MatchHistoryEntry::operator=(WhackAStoodentServer::MatchHistoryEntry&& matchHistoryEntry) noexcept
{
	yourScore = matchHistoryEntry.yourScore;
	yourName = matchHistoryEntry.yourName;
	opponentScore = matchHistoryEntry.opponentScore;
	opponentName = matchHistoryEntry.opponentName;
	return *this;
}
