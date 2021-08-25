#include <Messages/RequestPlayMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a request play message
/// </summary>
WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>(),
	playerRole(EPlayerRole::Hitter)
{
	// ...
}

/// <summary>
/// Constructs a request play message
/// </summary>
/// <param name="playerRole">Player role</param>
/// <param name="opponentName">Opponent name</param>
WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage(WhackAStoodentServer::EPlayerRole playerRole, std::wstring_view opponentName) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>(),
	playerRole(playerRole),
	opponentName(opponentName)
{
	// ...
}

/// <summary>
/// Destroys request play message
/// </summary>
WhackAStoodentServer::Messages::RequestPlayMessage::~RequestPlayMessage()
{
	// ...
}

/// <summary>
/// Gets the player role
/// </summary>
/// <returns>Player role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Messages::RequestPlayMessage::GetPlayerRole() const
{
	return playerRole;
}

/// <summary>
/// Gets the opponent's name
/// </summary>
/// <returns>Opponent's name</returns>
std::wstring_view WhackAStoodentServer::Messages::RequestPlayMessage::GetOpponentName() const
{
	return opponentName;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::RequestPlayMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>::Serialize(result);
	NumericSerializer::SerializeByte(static_cast<std::uint8_t>(playerRole), result);
	return StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::RequestPlayMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t player_role_index;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::RequestPlay>::Deserialize(data));
	next_bytes = NumericSerializer::DeserializeByte(next_bytes, player_role_index);
	playerRole = static_cast<EPlayerRole>(player_role_index);
	return StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}
