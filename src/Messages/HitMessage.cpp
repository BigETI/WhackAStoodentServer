#include <Messages/HitMessage.hpp>

WhackAStoodentServer::Messages::HitMessage::HitMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Hit>()
{
	// ...
}

WhackAStoodentServer::Messages::HitMessage::HitMessage(const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Hit>(),
	position(position)
{
	// ...
}

const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitMessage::GetPosition() const
{
	return position;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Hit>::Serialize(result);
	return position.Serialize(result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::HitMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Hit>::Deserialize(data));
	return position.Deserialize(next_bytes);
}
