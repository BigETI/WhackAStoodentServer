#include <Messages/PongMessage.hpp>
#include <Static/NumericSerializer.hpp>

WhackAStoodentServer::Messages::PongMessage::PongMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Pong>(),
	pongData(static_cast<int32_t>(0))
{
	// ...
}

WhackAStoodentServer::Messages::PongMessage::PongMessage(int32_t pongData) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Pong>(),
	pongData(pongData)
{
	// ...
}

WhackAStoodentServer::Messages::PongMessage::~PongMessage()
{
	// ...
}

std::int32_t WhackAStoodentServer::Messages::PongMessage::GetPongData() const
{
	return pongData;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PongMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Pong>::Serialize(result);
	return NumericSerializer::SerializeInteger(pongData, result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::PongMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Pong>::Deserialize(data));
	return NumericSerializer::DeserializeInteger(next_bytes, pongData);
}
