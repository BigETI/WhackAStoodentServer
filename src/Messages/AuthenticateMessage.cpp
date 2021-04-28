#include <Messages/AuthenticateMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>()
{
	// ...
}

WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage(const uuids::uuid& userID, const std::wstring& username) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>(),
	userID(userID),
	username(username)
{
	// ...
}

WhackAStoodentServer::Messages::AuthenticateMessage::~AuthenticateMessage()
{
	// ...
}

const uuids::uuid& WhackAStoodentServer::Messages::AuthenticateMessage::GetUserID() const
{
	return userID;
}

const std::wstring& WhackAStoodentServer::Messages::AuthenticateMessage::GetUsername() const
{
	return username;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::AuthenticateMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>::Serialize(result);
	UUIDs::SerializeUUID(userID, result);
	return StringSerializer::Serialize<std::uint8_t>(username, result);
}

std::span<const std::uint8_t> WhackAStoodentServer::Messages::AuthenticateMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>::Deserialize(data));
	next_bytes = UUIDs::DeserializeUUID(next_bytes, userID);
	return StringSerializer::DeserializeByteSizedString(next_bytes, username);
}
