#include <Messages/RequestPlayMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>(),
	playerRole(EPlayerRole::Hitter)
{
	// ...
}

WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage(WhackAStoodentServer::EPlayerRole playerRole, const std::wstring& opponentName) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>(),
	playerRole(playerRole),
	opponentName(opponentName)
{
	// ...
}

WhackAStoodentServer::Messages::RequestPlayMessage::~RequestPlayMessage()
{
	// ...
}

WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Messages::RequestPlayMessage::GetPlayerRole() const
{
	return playerRole;
}

const std::wstring& WhackAStoodentServer::Messages::RequestPlayMessage::GetOpponentName() const
{
	return opponentName;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::RequestPlayMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>::Serialize(result);
	NumericSerializer::SerializeByte(static_cast<std::uint8_t>(playerRole), result);
	return StringSerializer::SerializeByteSizedString(opponentName, result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::RequestPlayMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t player_role_index;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>::Deserialize(data));
	next_bytes = NumericSerializer::DeserializeByte(next_bytes, player_role_index);
	playerRole = static_cast<EPlayerRole>(player_role_index);
	return StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}
