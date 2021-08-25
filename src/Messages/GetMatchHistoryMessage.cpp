#include <Messages/GetMatchHistoryMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Construicts a get match history message
/// </summary>
WhackAStoodentServer::Messages::GetMatchHistoryMessage::GetMatchHistoryMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::GetMatchHistory>()
{
	// ...
}

/// <summary>
/// Destroys get match history message
/// </summary>
WhackAStoodentServer::Messages::GetMatchHistoryMessage::~GetMatchHistoryMessage()
{
	// ...
}
