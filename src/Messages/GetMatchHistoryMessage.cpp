#include <Messages/GetMatchHistoryMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Messages::GetMatchHistoryMessage::GetMatchHistoryMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::GetMatchHistory>()
{
	// ...
}

WhackAStoodentServer::Messages::GetMatchHistoryMessage::~GetMatchHistoryMessage()
{
	// ...
}
