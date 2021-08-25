#include <Messages/EndGameMessage.hpp>
#include <Static/CollectionSerializer.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs an end game message
/// </summary>
WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>()
{
	// ...
}

/// <summary>
/// Constructs an end game message
/// </summary>
/// <param name="matchHistory">Match history</param>
WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>(),
	matchHistory(matchHistory)
{
	// ...
}

/// <summary>
/// Constructs an end game message
/// </summary>
/// <param name="matchHistory">Match history</param>
WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>(),
	matchHistory(matchHistory)
{
	// ...
}

/// <summary>
/// Destroys end game message
/// </summary>
WhackAStoodentServer::Messages::EndGameMessage::~EndGameMessage()
{
	// ...
}

/// <summary>
/// Gets the current match history
/// </summary>
/// <returns>Match history</returns>
const std::vector<WhackAStoodentServer::MatchHistoryEntry>& WhackAStoodentServer::Messages::EndGameMessage::GetMatchHistory() const
{
	return matchHistory;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::EndGameMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>::Serialize(result);
	return WhackAStoodentServer::CollectionSerializer::SerializeIntegerSizedCollection<WhackAStoodentServer::MatchHistoryEntry>(std::span<const WhackAStoodentServer::MatchHistoryEntry>(matchHistory.begin(), matchHistory.end()), result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::EndGameMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>::Deserialize(data));
	return CollectionSerializer::DeserializeIntegerSizedCollection<WhackAStoodentServer::MatchHistoryEntry>(next_bytes, matchHistory);
}
