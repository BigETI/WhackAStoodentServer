#include <Messages/AcknowledgeAuthentificationMessage.hpp>
#include <Static/SessionCodes.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs an acknowledge authentification message
/// </summary>
WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::AcknowledgeAuthentificationMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::AcknowledgeAuthentification>()
{
	// ...
}

/// <summary>
/// Constructs an acknowledge authentification message
/// </summary>
/// <param name="userID">User ID</param>
/// <param name="sessionCode">Session code</param>
/// <param name="username">Username</param>
WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::AcknowledgeAuthentificationMessage(const uuids::uuid& userID, std::string_view sessionCode, std::wstring_view username) :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::AcknowledgeAuthentification>(),
	userID(userID),
	sessionCode(sessionCode),
	username(username)
{
	// ...
}

/// <summary>
/// Destroys acknowledge authentification message
/// </summary>
WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::~AcknowledgeAuthentificationMessage()
{
	// ...
}

/// <summary>
/// Gets the user ID
/// </summary>
/// <returns>User ID</returns>
const uuids::uuid& WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::GetUserID() const
{
	return userID;
}

/// <summary>
/// Gets the session code
/// </summary>
/// <returns>Session code</returns>
std::string_view WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::GetSessionCode() const
{
	return sessionCode;
}

/// <summary>
/// Gets the user name
/// </summary>
/// <returns>Username</returns>
std::wstring_view WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::GetUsername() const
{
	return username;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::AcknowledgeAuthentification>::Serialize(result);
	WhackAStoodentServer::UUIDs::SerializeUUID(userID, result);
	WhackAStoodentServer::SessionCodes::Serialize(sessionCode, result);
	return WhackAStoodentServer::StringSerializer::Serialize<std::uint8_t>(username, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<const std::uint8_t> WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage::Deserialize(std::span<const std::uint8_t> data)
{
	std::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::AcknowledgeAuthentification>::Deserialize(data));
	next_bytes = WhackAStoodentServer::UUIDs::DeserializeUUID(next_bytes, userID);
	next_bytes = WhackAStoodentServer::SessionCodes::Deserialize(next_bytes, sessionCode);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, username);
}
