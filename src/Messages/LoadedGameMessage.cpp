#include <Messages/LoadedGameMessage.hpp>

/// <summary>
/// Constructs a loaded game message
/// </summary>
WhackAStoodentServer::Messages::LoadedGameMessage::LoadedGameMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::LoadedGame>()
{
	// ...
}

/// <summary>
/// Destroys loaded game message
/// </summary>
WhackAStoodentServer::Messages::LoadedGameMessage::~LoadedGameMessage()
{
	// ...
}
