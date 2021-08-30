#include <Messages/ScoreMoleMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a score mole message
/// </summary>
WhackAStoodentServer::Messages::ScoreMoleMessage::ScoreMoleMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::ScoreMole>(),
	points(static_cast<std::int64_t>(0))
{
	// ...
}

/// <summary>
/// Constructs a score mole message
/// </summary>
/// <param name="points">Points</param>
WhackAStoodentServer::Messages::ScoreMoleMessage::ScoreMoleMessage(std::int64_t points) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::ScoreMole>(),
	points(points)
{
	// ...
}

/// <summary>
/// Destroys score mole message
/// </summary>
WhackAStoodentServer::Messages::ScoreMoleMessage::~ScoreMoleMessage()
{
	// ...
}

/// <summary>
/// Gets the points
/// </summary>
/// <returns>Points</returns>
std::int64_t WhackAStoodentServer::Messages::ScoreMoleMessage::GetPoints() const
{
	return points;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::ScoreMoleMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::ScoreMole>::Serialize(result);
	return WhackAStoodentServer::NumericSerializer::SerializeLong(points, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::ScoreMoleMessage::Deserialize(std::span<const std::uint8_t> data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::ScoreMole>::Deserialize(data));
	return WhackAStoodentServer::NumericSerializer::DeserializeLong(next_bytes, points);
}
