#include <Messages/LogMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

WhackAStoodentServer::Messages::LogMessage::LogMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Log>(),
	logLevel(ELogLevel::Info)
{
	// ...
}

WhackAStoodentServer::Messages::LogMessage::LogMessage(ELogLevel logLevel, const std::wstring& logMessage) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Log>(),
	logLevel(logLevel),
	logMessage(logMessage)
{
	// ...
}

WhackAStoodentServer::Messages::LogMessage::~LogMessage()
{
	// ...
}

WhackAStoodentServer::ELogLevel WhackAStoodentServer::Messages::LogMessage::GetLogLevel() const
{
	return logLevel;
}

const std::wstring& WhackAStoodentServer::Messages::LogMessage::GetLogMessage() const
{
	return logMessage;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::LogMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Log>::Serialize(result);
	NumericSerializer::SerializeByte(static_cast<std::uint8_t>(logLevel), result);
	StringSerializer::SerializeIntegerSizedString(logMessage, result);
	return result;
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::LogMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t log_level_index;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Log>::Deserialize(data));
	next_bytes = NumericSerializer::DeserializeByte(next_bytes, log_level_index);
	logLevel = static_cast<WhackAStoodentServer::ELogLevel>(log_level_index);
	return StringSerializer::DeserializeIntegerSizedString(next_bytes, logMessage);
}
