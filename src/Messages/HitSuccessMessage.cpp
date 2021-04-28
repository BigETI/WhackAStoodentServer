#include <Messages/HitSuccessMessage.hpp>
#include <Static/NumericSerializer.hpp>

WhackAStoodentServer::Messages::HitSuccessMessage::HitSuccessMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitSuccess>(),
	lookHole(WhackAStoodentServer::ELookHole::Top),
	points(static_cast<std::int64_t>(0))

{
	// ...
}

WhackAStoodentServer::Messages::HitSuccessMessage::HitSuccessMessage(WhackAStoodentServer::ELookHole lookHole, std::int64_t points, const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitSuccess>(),
	lookHole(lookHole),
	points(points),
	position(position)
{
	// ...
}

WhackAStoodentServer::Messages::HitSuccessMessage::~HitSuccessMessage()
{
	// ...
}

WhackAStoodentServer::ELookHole WhackAStoodentServer::Messages::HitSuccessMessage::GetLookHole() const
{
	return lookHole;
}

std::int64_t WhackAStoodentServer::Messages::HitSuccessMessage::GetPoints() const
{
	return points;
}

const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitSuccessMessage::GetPosition() const
{
	return position;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitSuccessMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitSuccess>::Serialize(result);
	NumericSerializer::SerializeByte(static_cast<std::uint8_t>(lookHole), result);
	NumericSerializer::SerializeLong(points, result);
	return position.Serialize(result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::HitSuccessMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t look_hole_index;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitSuccess>::Deserialize(data));
	next_bytes = NumericSerializer::DeserializeByte(next_bytes, look_hole_index);
	lookHole = static_cast<WhackAStoodentServer::ELookHole>(look_hole_index);
	next_bytes = NumericSerializer::DeserializeLong(next_bytes, points);
	return position.Deserialize(next_bytes);
}
