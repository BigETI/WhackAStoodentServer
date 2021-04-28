#include <Messages/ErrorMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

WhackAStoodentServer::Messages::ErrorMessage::ErrorMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Error>(),
	errorType(EErrorType::Unknown)
{
	// ...
}

WhackAStoodentServer::Messages::ErrorMessage::ErrorMessage(EErrorType errorType, const std::wstring& errorMessage) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Error>(),
	errorType(errorType),
	errorMessage(errorMessage)
{
	// ...
}

WhackAStoodentServer::Messages::ErrorMessage::~ErrorMessage()
{
	// ...
}

WhackAStoodentServer::EErrorType WhackAStoodentServer::Messages::ErrorMessage::GetErrorType() const
{
	return errorType;
}

const std::wstring& WhackAStoodentServer::Messages::ErrorMessage::GetErrorMessage() const
{
	return errorMessage;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::ErrorMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Error>::Serialize(result);
	NumericSerializer::SerializeByte(static_cast<std::uint8_t>(errorType), result);
	StringSerializer::SerializeIntegerSizedString(errorMessage, result);
	return result;
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::ErrorMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t error_type_index;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Error>::Deserialize(data));
	next_bytes = NumericSerializer::DeserializeByte(next_bytes, error_type_index);
	errorType = static_cast<WhackAStoodentServer::EErrorType>(error_type_index);
	return StringSerializer::DeserializeIntegerSizedString(next_bytes, errorMessage);
}
