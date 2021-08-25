#include <Messages/AcceptPlayRequestMessage.hpp>

/// <summary>
/// Constructs an accept playe request message
/// </summary>
WhackAStoodentServer::Messages::AcceptPlayRequestMessage::AcceptPlayRequestMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcceptPlayRequest>()
{
	// ...
}

/// <summary>
/// Destroys accept playe request message
/// </summary>
WhackAStoodentServer::Messages::AcceptPlayRequestMessage::~AcceptPlayRequestMessage()
{
	// ...
}
