#include <Messages/ScoreMoleMessage.hpp>
#include <Static/NumericSerializer.hpp>

WhackAStoodentServer::Messages::ScoreMoleMessage::ScoreMoleMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::ScoreMole>(),
	points(static_cast<std::int64_t>(0))
{
	// ...
}

WhackAStoodentServer::Messages::ScoreMoleMessage::ScoreMoleMessage(std::int64_t points) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::ScoreMole>(),
	points(points)
{
	// ...
}

WhackAStoodentServer::Messages::ScoreMoleMessage::~ScoreMoleMessage()
{
	// ...
}

std::int64_t WhackAStoodentServer::Messages::ScoreMoleMessage::GetPoints() const
{
	return points;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::ScoreMoleMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::ScoreMole>::Serialize(result);
	return NumericSerializer::SerializeLong(points, result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::ScoreMoleMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::ScoreMole>::Deserialize(data));
	return NumericSerializer::DeserializeLong(next_bytes, points);
}
