#include <Messages/HitFailMessage.hpp>

/// <summary>
/// Constructs a hit fail message
/// </summary>
WhackAStoodentServer::Messages::HitFailMessage::HitFailMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitFail>()

{
	// ...
}

/// <summary>
/// Constructs a hit fail message
/// </summary>
/// <param name="position">Position</param>
WhackAStoodentServer::Messages::HitFailMessage::HitFailMessage(const WhackAStoodentServer::Vector2D<float>& position) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitFail>(),
	position(position)
{
	// ...
}

/// <summary>
/// Destroys hit fail message
/// </summary>
WhackAStoodentServer::Messages::HitFailMessage::~HitFailMessage()
{
	// ...
}

/// <summary>
/// Gets the position
/// </summary>
/// <returns>Position</returns>
const WhackAStoodentServer::Vector2D<float>& WhackAStoodentServer::Messages::HitFailMessage::GetPosition() const
{
	return position;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::HitFailMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitFail>::Serialize(result);
	return position.Serialize(result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::HitFailMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::HitFail>::Deserialize(data));
	return position.Deserialize(next_bytes);
}
