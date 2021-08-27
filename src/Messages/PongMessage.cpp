#include <Messages/PongMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a pong message
/// </summary>
WhackAStoodentServer::Messages::PongMessage::PongMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Pong>(),
	pongData(static_cast<int32_t>(0))
{
	// ...
}

/// <summary>
/// Constructs a pong message
/// </summary>
/// <param name="pongData">Pong data</param>
WhackAStoodentServer::Messages::PongMessage::PongMessage(int32_t pongData) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Pong>(),
	pongData(pongData)
{
	// ...
}

/// <summary>
/// Destroys pong message
/// </summary>
WhackAStoodentServer::Messages::PongMessage::~PongMessage()
{
	// ...
}

/// <summary>
/// Gets the pong data
/// </summary>
/// <returns>Pong data</returns>
std::int32_t WhackAStoodentServer::Messages::PongMessage::GetPongData() const
{
	return pongData;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PongMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Pong>::Serialize(result);
	return NumericSerializer::SerializeInteger(pongData, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::PongMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Pong>::Deserialize(data));
	return NumericSerializer::DeserializeInteger(next_bytes, pongData);
}
