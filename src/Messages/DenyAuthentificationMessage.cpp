#include <Messages/DenyAuthentificationMessage.hpp>

/// <summary>
/// Constructs a deny authentification message
/// </summary>
WhackAStoodentServer::Messages::DenyAuthentificationMessage::DenyAuthentificationMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::DenyAuthentification>()
{
	// ...
}

/// <summary>
/// Destroys deny authentification message
/// </summary>
WhackAStoodentServer::Messages::DenyAuthentificationMessage::~DenyAuthentificationMessage()
{
	// ...
}
