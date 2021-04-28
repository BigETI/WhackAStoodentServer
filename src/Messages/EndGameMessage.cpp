#include <Messages/EndGameMessage.hpp>
#include <Static/CollectionSerializer.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>()
{
	// ...
}

WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>(),
	matchHistory(matchHistory)
{
	// ...
}

WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>(),
	matchHistory(matchHistory)
{
	// ...
}

WhackAStoodentServer::Messages::EndGameMessage::~EndGameMessage()
{
	// ...
}

const std::vector<WhackAStoodentServer::MatchHistoryEntry>& WhackAStoodentServer::Messages::EndGameMessage::GetMatchHistory() const
{
	return matchHistory;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::EndGameMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>::Serialize(result);
	return WhackAStoodentServer::CollectionSerializer::SerializeIntegerCollection<WhackAStoodentServer::MatchHistoryEntry>(std::span<const WhackAStoodentServer::MatchHistoryEntry>(matchHistory.begin(), matchHistory.end()), result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::EndGameMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::EndGame>::Deserialize(data));
	return CollectionSerializer::DeserializeIntegerCollection<WhackAStoodentServer::MatchHistoryEntry>(next_bytes, matchHistory);
}
