#include <Messages/PingMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a ping message
/// </summary>
WhackAStoodentServer::Messages::PingMessage::PingMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Ping>(),
	pingData(static_cast<std::int32_t>(0))
{
	// ...
}

/// <summary>
/// Constructs a ping message
/// </summary>
/// <param name="pingData">Ping data</param>
WhackAStoodentServer::Messages::PingMessage::PingMessage(std::int32_t pingData) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Ping>(),
	pingData(pingData)
{
	// ...
}

/// <summary>
/// Destroys ping message
/// </summary>
WhackAStoodentServer::Messages::PingMessage::~PingMessage()
{
	// ...
}

/// <summary>
/// Gets the ping data
/// </summary>
/// <returns>Ping data</returns>
std::int32_t WhackAStoodentServer::Messages::PingMessage::GetPingData() const
{
	return pingData;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PingMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Ping>::Serialize(result);
	return WhackAStoodentServer::NumericSerializer::SerializeInteger(pingData, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::PingMessage::Deserialize(std::span<const std::uint8_t> data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Ping>::Deserialize(data));
	return WhackAStoodentServer::NumericSerializer::DeserializeInteger(next_bytes, pingData);
}
