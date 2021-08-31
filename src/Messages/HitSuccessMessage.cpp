#include <Messages/HitSuccessMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a hit message
/// </summary>
WhackAStoodentServer::Messages::HitSuccessMessage::HitSuccessMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitSuccess>(),
	lookHole(static_cast<std::size_t>(0)),
	points(static_cast<std::int64_t>(0))

{
	// ...
}

/// <summary>
/// Constructs a hit message
/// </summary>
/// <param name="lookHole">Look hole</param>
/// <param name="points">Points</param>
/// <param name="position">Position</param>
WhackAStoodentServer::Messages::HitSuccessMessage::HitSuccessMessage(std::size_t lookHole, std::int64_t points, const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitSuccess>(),
	lookHole(lookHole),
	points(points),
	position(position)
{
	// ...
}

/// <summary>
/// Destroys hit message
/// </summary>
WhackAStoodentServer::Messages::HitSuccessMessage::~HitSuccessMessage()
{
	// ...
}

/// <summary>
/// Get the look hole
/// </summary>
/// <returns>Look hole</returns>
std::size_t WhackAStoodentServer::Messages::HitSuccessMessage::GetLookHole() const
{
	return lookHole;
}

/// <summary>
/// Gets the points
/// </summary>
/// <returns>Points</returns>
std::int64_t WhackAStoodentServer::Messages::HitSuccessMessage::GetPoints() const
{
	return points;
}

/// <summary>
/// Gets the position
/// </summary>
/// <returns>Position</returns>
const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitSuccessMessage::GetPosition() const
{
	return position;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitSuccessMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitSuccess>::Serialize(result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(lookHole), result);
	WhackAStoodentServer::NumericSerializer::SerializeLong(points, result);
	return position.Serialize(result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::HitSuccessMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	std::uint8_t look_hole_index;
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitSuccess>::Deserialize(data));
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, look_hole_index);
	lookHole = static_cast<std::size_t>(look_hole_index);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeLong(next_bytes, points);
	return position.Deserialize(next_bytes);
}
