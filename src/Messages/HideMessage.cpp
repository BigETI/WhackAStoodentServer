#include <Messages/HideMessage.hpp>

WhackAStoodentServer::Messages::HideMessage::HideMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Hide>()
{
	// ...
}

WhackAStoodentServer::Messages::HideMessage::~HideMessage()
{
	// ...
}
