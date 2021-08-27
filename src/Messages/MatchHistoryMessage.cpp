#include <Messages/MatchHistoryMessage.hpp>
#include <Static/CollectionSerializer.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs a match history message
/// </summary>
WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::MatchHistory>()
{
	// ...
}

/// <summary>
/// Constructs a match history message
/// </summary>
/// <param name="matchHistory">Match history</param>
WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::MatchHistory>(),
	matchHistory(matchHistory)
{
	// ...
}

/// <summary>
/// Constructs a match history message
/// </summary>
/// <param name="matchHistory">Match history</param>
WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::MatchHistory>(),
	matchHistory(matchHistory)
{
	// ...
}

/// <summary>
/// Destroys match history message
/// </summary>
WhackAStoodentServer::Messages::MatchHistoryMessage::~MatchHistoryMessage()
{
	// ...
}

/// <summary>
/// Gets match history
/// </summary>
/// <returns>Match history</returns>
const std::span<const WhackAStoodentServer::MatchHistoryEntry> WhackAStoodentServer::Messages::MatchHistoryMessage::GetMatchHistory() const
{
	return matchHistory;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::MatchHistoryMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::MatchHistory>::Serialize(result);
	return WhackAStoodentServer::CollectionSerializer::SerializeIntegerSizedCollection<WhackAStoodentServer::MatchHistoryEntry>(std::span<const WhackAStoodentServer::MatchHistoryEntry>(matchHistory.begin(), matchHistory.end()), result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::MatchHistoryMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::MatchHistory>::Deserialize(data));
	return WhackAStoodentServer::CollectionSerializer::DeserializeIntegerSizedCollection<WhackAStoodentServer::MatchHistoryEntry>(next_bytes, matchHistory);
}
