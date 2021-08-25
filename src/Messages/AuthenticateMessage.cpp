#include <Messages/AuthenticateMessage.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs an authenticate message
/// </summary>
WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>()
{
	// ...
}

/// <summary>
/// Constructs an authenticate message
/// </summary>
/// <param name="userID">User ID</param>
/// <param name="username">Username</param>
WhackAStoodentServer::Messages::AuthenticateMessage::AuthenticateMessage(const uuids::uuid& userID, std::wstring_view username) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>(),
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
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>::Serialize(result);
	UUIDs::SerializeUUID(userID, result);
	return StringSerializer::Serialize<std::uint8_t>(username, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::AuthenticateMessage::Deserialize(const std::span<const std::uint8_t>& data)
{
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::Authenticate>::Deserialize(data));
	next_bytes = UUIDs::DeserializeUUID(next_bytes, userID);
	return StringSerializer::DeserializeByteSizedString(next_bytes, username);
}
