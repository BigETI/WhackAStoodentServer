#include <Messages/LogMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a log message
/// </summary>
WhackAStoodentServer::Messages::LogMessage::LogMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Log>(),
	logLevel(ELogLevel::Information)
{
	// ...
}

/// <summary>
/// Constructs a log message
/// </summary>
/// <param name="logLevel">Log level</param>
/// <param name="logMessage">Log message</param>
WhackAStoodentServer::Messages::LogMessage::LogMessage(ELogLevel logLevel, std::wstring_view logMessage) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Log>(),
	logLevel(logLevel),
	logMessage(logMessage)
{
	// ...
}

/// <summary>
/// Destroys log message
/// </summary>
WhackAStoodentServer::Messages::LogMessage::~LogMessage()
{
	// ...
}

/// <summary>
/// Gets the log level
/// </summary>
/// <returns>Log level</returns>
WhackAStoodentServer::ELogLevel WhackAStoodentServer::Messages::LogMessage::GetLogLevel() const
{
	return logLevel;
}

/// <summary>
/// Gets the log message
/// </summary>
/// <returns>Log message</returns>
std::wstring_view WhackAStoodentServer::Messages::LogMessage::GetLogMessage() const
{
	return logMessage;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::LogMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Log>::Serialize(result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(logLevel), result);
	WhackAStoodentServer::StringSerializer::SerializeIntegerSizedString(logMessage, result);
	return result;
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::LogMessage::Deserialize(std::span<const std::uint8_t> data)
{
	std::uint8_t log_level_index;
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Log>::Deserialize(data));
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, log_level_index);
	logLevel = static_cast<WhackAStoodentServer::ELogLevel>(log_level_index);
	return WhackAStoodentServer::StringSerializer::DeserializeIntegerSizedString(next_bytes, logMessage);
}
