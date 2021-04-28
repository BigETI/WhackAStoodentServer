#include <Messages/DenyAuthentificationMessage.hpp>

WhackAStoodentServer::Messages::DenyAuthentificationMessage::DenyAuthentificationMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyAuthentification>()
{
	// ...
}

WhackAStoodentServer::Messages::DenyAuthentificationMessage::~DenyAuthentificationMessage()
{
	// ...
}
