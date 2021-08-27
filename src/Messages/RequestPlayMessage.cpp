#include <Messages/RequestPlayMessage.hpp>
#include <Static/NumericCollectionSerializer.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a request play message
/// </summary>
WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::RequestPlay>()
{
	// ...
}

/// <summary>
/// Constructs a request play message
/// </summary>
/// <param name="playerRole">Player role</param>
/// <param name="opponentSessionCode">Opponent's session code</param>
/// <param name="opponentName">Opponent's name</param>
WhackAStoodentServer::Messages::RequestPlayMessage::RequestPlayMessage(std::string_view opponentSessionCode, std::wstring_view opponentName) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::RequestPlay>(),
	opponentSessionCode(opponentSessionCode),
	opponentName(opponentName)
{
	if (!WhackAStoodentServer::SessionCodes::IsSessionCodeValid(opponentSessionCode))
	{
		throw std::invalid_argument("Opponent session code is not valid.");
	}
}

/// <summary>
/// Destroys request play message
/// </summary>
WhackAStoodentServer::Messages::RequestPlayMessage::~RequestPlayMessage()
{
	// ...
}

/// <summary>
/// Gets the opponent's session code
/// </summary>
/// <returns>Opponent's session code</returns>
std::string_view WhackAStoodentServer::Messages::RequestPlayMessage::GetOpponentSessionCode() const
{
	return opponentSessionCode;
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
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::RequestPlay>::Serialize(result);
	WhackAStoodentServer::SessionCodes::Serialize(opponentSessionCode, result);
	return WhackAStoodentServer::StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::RequestPlayMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::RequestPlay>::Deserialize(data));
	next_bytes = WhackAStoodentServer::SessionCodes::Deserialize(next_bytes, opponentSessionCode);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}
