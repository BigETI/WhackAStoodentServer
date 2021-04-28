#include <Messages/AcceptPlayRequestMessage.hpp>

WhackAStoodentServer::Messages::AcceptPlayRequestMessage::AcceptPlayRequestMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcceptPlayRequest>()
{
	// ...
}

WhackAStoodentServer::Messages::AcceptPlayRequestMessage::~AcceptPlayRequestMessage()
{
	// ...
}
