#include <stdexcept>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Messages/PlayWithSessionCodeMessage.hpp>
#include <Static/SessionCodes.hpp>

/// <summary>
/// Constructs a play with session code message
/// </summary>
WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>(),
	sessionCode(SessionCodeCharacterCount, '0')
{
	// ...
}

/// <summary>
/// Constructs a play with session code message
/// </summary>
/// <param name="sessionCode">Session code</param>
WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage(std::string_view sessionCode) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>(),
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
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>::Serialize(result);
	std::size_t offset(result.size());
	result.resize(result.size() + (SessionCodeCharacterCount * sizeof(std::string::value_type)));
	std::memcpy(result.data() + offset, sessionCode.data(), SessionCodeCharacterCount * sizeof(std::string::value_type));
	return result;
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>::Deserialize(data));
	if (next_bytes.size() < SessionCodeCharacterCount)
	{
		throw DeserializationFailedException();
	}
	std::memcpy(sessionCode.data(), next_bytes.data(), SessionCodeCharacterCount * sizeof(std::string::value_type));
	return next_bytes.subspan<SessionCodeCharacterCount * sizeof(std::string::value_type)>();
}
