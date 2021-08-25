#include <Messages/LookMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a look message
/// </summary>
WhackAStoodentServer::Messages::LookMessage::LookMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Look>(),
	lookHole(WhackAStoodentServer::ELookHole::Top)
{
	// ...
}

/// <summary>
/// Constructs a look message
/// </summary>
/// <param name="lookHole">Look hole</param>
WhackAStoodentServer::Messages::LookMessage::LookMessage(WhackAStoodentServer::ELookHole lookHole) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Look>(),
	lookHole(lookHole)
{
	// ...
}

/// <summary>
/// Gets the look hole
/// </summary>
/// <returns>Look hole</returns>
WhackAStoodentServer::ELookHole WhackAStoodentServer::Messages::LookMessage::GetLookHole() const
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
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Look>::Serialize(result);
	return NumericSerializer::SerializeByte(static_cast<std::uint8_t>(lookHole), result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::LookMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t look_hole_index;
	std::span<std::uint8_t const> ret(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Look>::Deserialize(data));
	ret = NumericSerializer::DeserializeByte(ret, look_hole_index);
	lookHole = static_cast<WhackAStoodentServer::ELookHole>(look_hole_index);
	return ret;
}
