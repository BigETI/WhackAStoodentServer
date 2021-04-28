#include <Messages/AcknowledgeAuthentificationMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::AcknowledgeAuthentificationMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcknowledgeAuthentification>()
{
	// ...
}

WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::AcknowledgeAuthentificationMessage(const uuids::uuid& userID, const std::wstring& username) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcknowledgeAuthentification>(),
	userID(userID),
	username(username)
{
	// ...
}

WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::~AcknowledgeAuthentificationMessage()
{
	// ...
}

const uuids::uuid& WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::GetUserID() const
{
	return userID;
}

const std::wstring& WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::GetUsername() const
{
	return username;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcknowledgeAuthentification>::Serialize(result);
	UUIDs::SerializeUUID(userID, result);
	return StringSerializer::Serialize<std::uint8_t>(username, result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::AcknowledgeAuthentification>::Deserialize(data));
	next_bytes = UUIDs::DeserializeUUID(next_bytes, userID);
	return StringSerializer::DeserializeByteSizedString(next_bytes, username);
}
