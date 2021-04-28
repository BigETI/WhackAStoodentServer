#include <stdexcept>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Messages/PlayWithSessionCodeMessage.hpp>

WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>(),
	sessionCode(SessionCodeCharacterCount, '0')
{
	// ...
}

WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::PlayWithSessionCodeMessage(const std::string& sessionCode) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>(),
	sessionCode(sessionCode)
{
	if (sessionCode.length() != SessionCodeCharacterCount)
	{
		throw std::invalid_argument("Parameter \"sessionCode\" must be 6 characters long.");
	}
	for (const char& character : sessionCode)
	{
		if (!std::isalnum(character))
		{
			throw std::invalid_argument("Parameter \"sessionID\" must be alpha numeric.");
		}
	}
}

WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::~PlayWithSessionCodeMessage()
{
	// ...
}

const std::string& WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::GetSessionCode() const
{
	return sessionCode;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::PlayWithSessionCodeMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::PlayWithSessionCode>::Serialize(result);
	std::size_t offset(result.size());
	result.resize(result.size() + (SessionCodeCharacterCount * sizeof(std::string::value_type)));
	std::memcpy(result.data() + offset, sessionCode.data(), SessionCodeCharacterCount * sizeof(std::string::value_type));
	return result;
}

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
