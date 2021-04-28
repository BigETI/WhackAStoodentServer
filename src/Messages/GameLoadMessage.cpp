#include <Messages/LoadedGameMessage.hpp>

WhackAStoodentServer::Messages::LoadedGameMessage::LoadedGameMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::LoadedGame>()
{
	// ...
}

WhackAStoodentServer::Messages::LoadedGameMessage::~LoadedGameMessage()
{
	// ...
}
