#include <stdexcept>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Messages/PlayWithSessionCodeMessage.hpp>
#include <Static/SessionCodes.hpp>

/// <summary>
/// Constructs a play with session code message
/// </summary>
WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::PlayWithSessionCode>(),
	sessionCode(SessionCodeCharacterCount, '0')
{
	// ...
}

/// <summary>
/// Constructs a play with session code message
/// </summary>
/// <param name="sessionCode">Session code</param>
WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage(std::string_view sessionCode) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::PlayWithSessionCode>(),
	sessionCode(sessionCode)
{
	if (!SessionCodes::IsSessionCodeValid(sessionCode))
	{
		throw std::invalid_argument("Parameter \"sessionCode\" is not valid.");
	}
}

/// <summary>
/// Destroys play with session code message
/// </summary>
WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::~PlayWithSessionCodeMessage()
{
	// ...
}

/// <summary>
/// Gets the session code
/// </summary>
/// <returns>Session code</returns>
std::string_view WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::GetSessionCode() const
{
	return sessionCode;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::PlayWithSessionCode>::Serialize(result);
	return WhackAStoodentServer::SessionCodes::Serialize(sessionCode, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::PlayWithSessionCode>::Deserialize(data));
	return WhackAStoodentServer::SessionCodes::Deserialize(next_bytes, sessionCode);
}
