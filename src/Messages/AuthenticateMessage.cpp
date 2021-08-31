#include <Messages/AuthenticateMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs an authenticate message
/// </summary>
WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Authenticate>()
{
	// ...
}

/// <summary>
/// Constructs an authenticate message
/// </summary>
/// <param name="userID">User ID</param>
/// <param name="username">Username</param>
WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage(const uuids::uuid& userID, std::wstring_view username) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Authenticate>(),
	userID(userID),
	username(username)
{
	// ...
}

/// <summary>
/// Destroys authenticate message
/// </summary>
WhackAStoodentServer::Messages::AuthenticateMessage::~AuthenticateMessage()
{
	// ...
}

/// <summary>
/// Gets the user ID
/// </summary>
/// <returns>User ID</returns>
const uuids::uuid& WhackAStoodentServer::Messages::AuthenticateMessage::GetUserID() const
{
	return userID;
}

/// <summary>
/// Gets the username
/// </summary>
/// <returns>Username</returns>
std::wstring_view WhackAStoodentServer::Messages::AuthenticateMessage::GetUsername() const
{
	return username;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::AuthenticateMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Authenticate>::Serialize(result);
	WhackAStoodentServer::UUIDs::SerializeUUID(userID, result);
	return WhackAStoodentServer::StringSerializer::SerializeByteSizedString(username, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::AuthenticateMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::Authenticate>::Deserialize(data));
	next_bytes = WhackAStoodentServer::UUIDs::DeserializeUUID(next_bytes, userID);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, username);
}
