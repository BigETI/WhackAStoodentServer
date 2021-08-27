#include <Messages/PlayWithRandomMessage.hpp>

/// <summary>
/// Constructs a play with random message
/// </summary>
WhackAStoodentServer::Messages::PlayWithRandomMessage::PlayWithRandomMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::PlayWithRandom>()
{
	// ...
}

/// <summary>
/// Destroys play with random message
/// </summary>
WhackAStoodentServer::Messages::PlayWithRandomMessage::~PlayWithRandomMessage()
{
	// ...
}
