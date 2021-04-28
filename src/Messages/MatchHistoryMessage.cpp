#include <Messages/MatchHistoryMessage.hpp>
#include <Static/CollectionSerializer.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::MatchHistory>()
{
	// ...
}

WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::MatchHistory>(),
	matchHistory(matchHistory)
{
	// ...
}

WhackAStoodentServer::Messages::MatchHistoryMessage::MatchHistoryMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::MatchHistory>(),
	matchHistory(matchHistory)
{
	// ...
}

WhackAStoodentServer::Messages::MatchHistoryMessage::~MatchHistoryMessage()
{
	// ...
}

const std::vector<WhackAStoodentServer::MatchHistoryEntry>& WhackAStoodentServer::Messages::MatchHistoryMessage::GetMatchHistory() const
{
	return matchHistory;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::MatchHistoryMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::MatchHistory>::Serialize(result);
	return WhackAStoodentServer::CollectionSerializer::SerializeIntegerCollection<WhackAStoodentServer::MatchHistoryEntry>(std::span<const WhackAStoodentServer::MatchHistoryEntry>(matchHistory.begin(), matchHistory.end()), result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::MatchHistoryMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::MatchHistory>::Deserialize(data));
	return CollectionSerializer::DeserializeIntegerCollection<WhackAStoodentServer::MatchHistoryEntry>(next_bytes, matchHistory);
}
