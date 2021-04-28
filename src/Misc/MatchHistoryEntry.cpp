#include <Misc/MatchHistoryEntry.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry() :
	yourScore(static_cast<std::int64_t>(0)),
	opponentScore(static_cast<std::int64_t>(0))
{
	// ...
}

WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(const WhackAStoodentServer::MatchHistoryEntry& matchHistoryEntry) :
	yourScore(matchHistoryEntry.yourScore),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentName(matchHistoryEntry.opponentName)
{
	// ...
}

WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(WhackAStoodentServer::MatchHistoryEntry&& matchHistoryEntry) :
	yourScore(matchHistoryEntry.yourScore),
	yourName(matchHistoryEntry.yourName),
	opponentScore(matchHistoryEntry.opponentScore),
	opponentName(matchHistoryEntry.opponentName)
{
	// ...
}

WhackAStoodentServer::MatchHistoryEntry::MatchHistoryEntry(std::int64_t yourScore, std::wstring yourName, std::int64_t opponentScore, std::wstring opponentName) :
	yourScore(yourScore),
	yourName(yourName),
	opponentScore(opponentScore),
	opponentName(opponentName)
{
	// ...
}

WhackAStoodentServer::MatchHistoryEntry::~MatchHistoryEntry()
{
	// ...
}

std::int64_t WhackAStoodentServer::MatchHistoryEntry::GetYourScore() const
{
	return yourScore;
}

const std::wstring& WhackAStoodentServer::MatchHistoryEntry::GetYourName() const
{
	return yourName;
}

std::int64_t WhackAStoodentServer::MatchHistoryEntry::GetOpponentScore() const
{
	return opponentScore;
}

const std::wstring& WhackAStoodentServer::MatchHistoryEntry::GetOpponentName() const
{
	return opponentName;
}

std::vector<std::uint8_t>& WhackAStoodentServer::MatchHistoryEntry::Serialize(std::vector<std::uint8_t>& result) const
{
	NumericSerializer::SerializeLong(yourScore, result);
	StringSerializer::SerializeByteSizedString(yourName, result);
	NumericSerializer::SerializeLong(opponentScore, result);
	return StringSerializer::SerializeByteSizedString(opponentName, result);
}

std::span<std::uint8_t const> WhackAStoodentServer::MatchHistoryEntry::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(NumericSerializer::DeserializeLong(data, yourScore));
	next_bytes = StringSerializer::DeserializeByteSizedString(next_bytes, yourName);
	next_bytes = NumericSerializer::DeserializeLong(next_bytes, opponentScore);
	return StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}

WhackAStoodentServer::MatchHistoryEntry& WhackAStoodentServer::MatchHistoryEntry::operator=(const WhackAStoodentServer::MatchHistoryEntry& matchHistoryEntry)
{
	yourScore = matchHistoryEntry.yourScore;
	yourName = matchHistoryEntry.yourName;
	opponentScore = matchHistoryEntry.opponentScore;
	opponentName = matchHistoryEntry.opponentName;
	return *this;
}

WhackAStoodentServer::MatchHistoryEntry& WhackAStoodentServer::MatchHistoryEntry::operator=(WhackAStoodentServer::MatchHistoryEntry&& matchHistoryEntry) noexcept
{
	yourScore = matchHistoryEntry.yourScore;
	yourName = matchHistoryEntry.yourName;
	opponentScore = matchHistoryEntry.opponentScore;
	opponentName = matchHistoryEntry.opponentName;
	return *this;
}
