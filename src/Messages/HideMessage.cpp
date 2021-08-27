#include <Messages/HideMessage.hpp>

/// <summary>
/// Constructs a hide message
/// </summary>
WhackAStoodentServer::Messages::HideMessage::HideMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Hide>()
{
	// ...
}

/// <summary>
/// Destroys hide message
/// </summary>
WhackAStoodentServer::Messages::HideMessage::~HideMessage()
{
	// ...
}
