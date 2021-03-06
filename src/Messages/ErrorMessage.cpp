#include <Messages/ErrorMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs an error message
/// </summary>
WhackAStoodentServer::Messages::ErrorMessage::ErrorMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Error>(),
	errorType(EErrorType::Unknown)
{
	// ...
}

/// <summary>
/// Constructs an error message
/// </summary>
/// <param name="errorType">Error type</param>
/// <param name="errorMessage">Error message</param>
WhackAStoodentServer::Messages::ErrorMessage::ErrorMessage(EErrorType errorType, std::wstring_view errorMessage) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Error>(),
	errorType(errorType),
	errorMessage(errorMessage)
{
	// ...
}

/// <summary>
/// Destroys error message
/// </summary>
WhackAStoodentServer::Messages::ErrorMessage::~ErrorMessage()
{
	// ...
}

/// <summary>
/// Gets the error type
/// </summary>
/// <returns>Error type</returns>
WhackAStoodentServer::EErrorType WhackAStoodentServer::Messages::ErrorMessage::GetErrorType() const
{
	return errorType;
}

/// <summary>
/// Gets the error message
/// </summary>
/// <returns>Error message</returns>
std::wstring_view WhackAStoodentServer::Messages::ErrorMessage::GetErrorMessage() const
{
	return errorMessage;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::ErrorMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Error>::Serialize(result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(errorType), result);
	WhackAStoodentServer::StringSerializer::SerializeIntegerSizedString(errorMessage, result);
	return result;
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::ErrorMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	std::uint8_t error_type_index;
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Error>::Deserialize(data));
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, error_type_index);
	errorType = static_cast<WhackAStoodentServer::EErrorType>(error_type_index);
	return WhackAStoodentServer::StringSerializer::DeserializeIntegerSizedString(next_bytes, errorMessage);
}
