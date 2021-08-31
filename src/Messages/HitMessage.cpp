#include <Messages/HitMessage.hpp>

/// <summary>
/// Constructs a hit message
/// </summary>
WhackAStoodentServer::Messages::HitMessage::HitMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Hit>()
{
	// ...
}

/// <summary>
/// Constructs a hit message
/// </summary>
/// <param name="position">Position</param>
WhackAStoodentServer::Messages::HitMessage::HitMessage(const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Hit>(),
	position(position)
{
	// ...
}

/// <summary>
/// Destroys hit message
/// </summary>
WhackAStoodentServer::Messages::HitMessage::~HitMessage()
{
	// ...
}

/// <summary>
/// Gets the position
/// </summary>
/// <returns></returns>
const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitMessage::GetPosition() const
{
	return position;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Hit>::Serialize(result);
	return position.Serialize(result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::HitMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Hit>::Deserialize(data));
	return position.Deserialize(next_bytes);
}
