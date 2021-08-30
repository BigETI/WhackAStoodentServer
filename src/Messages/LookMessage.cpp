#include <Messages/LookMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a look message
/// </summary>
WhackAStoodentServer::Messages::LookMessage::LookMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Look>(),
	lookHole(static_cast<std::size_t>(0))
{
	// ...
}

/// <summary>
/// Constructs a look message
/// </summary>
/// <param name="lookHole">Look hole</param>
WhackAStoodentServer::Messages::LookMessage::LookMessage(std::size_t lookHole) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Look>(),
	lookHole(lookHole)
{
	// ...
}

/// <summary>
/// Gets the look hole
/// </summary>
/// <returns>Look hole</returns>
std::size_t WhackAStoodentServer::Messages::LookMessage::GetLookHole() const
{
	return lookHole;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::LookMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Look>::Serialize(result);
	return WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(lookHole), result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::LookMessage::Deserialize(std::span<const std::uint8_t> data)
{
	std::uint8_t look_hole_index;
	std::span<const std::uint8_t> ret(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Look>::Deserialize(data));
	ret = WhackAStoodentServer::NumericSerializer::DeserializeByte(ret, look_hole_index);
	lookHole = static_cast<std::size_t>(look_hole_index);
	return ret;
}
