#include <Misc/MatchHistoryEntry.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a match history entry
/// </summary>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry() :
	yourScore(static_cast<std::int64_t>(0)),
	yourRole(WhackAStoodentServer::EPlayerRole::Hitter),
	opponentScore(static_cast<std::int64_t>(0)),
	opponentRole(WhackAStoodentServer::EPlayerRole::Mole)
{
	// ...
}

/// <summary>
/// Constructs a match history entry
/// </summary>
/// <param name="matchHistoryEntry">Match history entry</param>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(const WhackAStoodentServer::MatchHistoryEntry& matchHistoryEntry) :
	yourScore(matchHistoryEntry.yourScore),
	yourRole(matchHistoryEntry.yourRole),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentRole(matchHistoryEntry.opponentRole),
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
	yourRole(matchHistoryEntry.yourRole),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentRole(matchHistoryEntry.opponentRole),
	opponentName(matchHistoryEntry.opponentName)
{
	// ...
}

/// <summary>
/// Constructs a match history entry
/// </summary>
/// <param name="yourScore">Your score</param>
/// <param name="yourRole">Your role</param>
/// <param name="yourName">Your name</param>
/// <param name="opponentScore">Opponent's score</param>
/// <param name="opponentRole">Opponent's role</param>
/// <param name="opponentName">Opponent's name</param>
WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(std::int64_t yourScore, WhackAStoodentServer::EPlayerRole yourRole, std::wstring_view yourName, std::int64_t opponentScore, WhackAStoodentServer::EPlayerRole opponentRole, std::wstring_view opponentName) :
	yourScore(yourScore),
	yourRole(yourRole),
	yourName(yourName),
	opponentScore(opponentScore),
	opponentRole(opponentRole),
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
/// Gets your role
/// </summary>
/// <returns>Your role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::MatchHistoryEntry::GetYourRole() const
{
	return yourRole;
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
/// Gets opponent's role
/// </summary>
/// <returns>Opponent's role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::MatchHistoryEntry::GetOpponentRole() const
{
	return opponentRole;
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
	WhackAStoodentServer::NumericSerializer::SerializeLong(yourScore, result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(yourRole), result);
	WhackAStoodentServer::StringSerializer::SerializeByteSizedString(yourName, result);
	WhackAStoodentServer::NumericSerializer::SerializeLong(opponentScore, result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(opponentRole), result);
	return WhackAStoodentServer::StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::MatchHistoryEntry::Deserialize(std::span<const std::uint8_t> data)
{
	std::uint8_t role;
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::NumericSerializer::DeserializeLong(data, yourScore));
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, role);
	yourRole = static_cast<WhackAStoodentServer::EPlayerRole>(role);
	next_bytes = WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, yourName);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeLong(next_bytes, opponentScore);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, role);
	opponentRole = static_cast<WhackAStoodentServer::EPlayerRole>(role);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
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
