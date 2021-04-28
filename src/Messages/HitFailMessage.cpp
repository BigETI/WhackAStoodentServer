#include <Messages/HitFailMessage.hpp>

WhackAStoodentServer::Messages::HitFailMessage::HitFailMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitFail>()

{
	// ...
}

WhackAStoodentServer::Messages::HitFailMessage::HitFailMessage(const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitFail>(),
	position(position)
{
	// ...
}

WhackAStoodentServer::Messages::HitFailMessage::~HitFailMessage()
{
	// ...
}

const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitFailMessage::GetPosition() const
{
	return position;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitFailMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitFail>::Serialize(result);
	return position.Serialize(result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::HitFailMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::HitFail>::Deserialize(data));
	return position.Deserialize(next_bytes);
}
