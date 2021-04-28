#include <Messages/PlayWithRandomMessage.hpp>

WhackAStoodentServer::Messages::PlayWithRandomMessage::PlayWithRandomMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithRandom>()
{
	// ...
}

WhackAStoodentServer::Messages::PlayWithRandomMessage::~PlayWithRandomMessage()
{
	// ...
}
