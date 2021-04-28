#include <Messages/PingMessage.hpp>
#include <Static/NumericSerializer.hpp>

WhackAStoodentServer::Messages::PingMessage::PingMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Ping>(),
	pingData(static_cast<std::int32_t>(0))
{
	// ...
}

WhackAStoodentServer::Messages::PingMessage::PingMessage(std::int32_t pingData) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Ping>(),
	pingData(pingData)
{
	// ...
}

WhackAStoodentServer::Messages::PingMessage::~PingMessage()
{
	// ...
}

std::int32_t WhackAStoodentServer::Messages::PingMessage::GetPingData() const
{
	return pingData;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PingMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Ping>::Serialize(result);
	return NumericSerializer::SerializeInteger(pingData, result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::PingMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Ping>::Deserialize(data));
	return NumericSerializer::DeserializeInteger(next_bytes, pingData);
}
