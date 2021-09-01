#include <Messages/EndGameMessage.hpp>
#include <Static/CollectionSerializer.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs an end game message
/// </summary>
WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::EndGame>()
{
	// ...
}

/// <summary>
/// Constructs an end game message
/// </summary>
/// <param name="sessionID">Session ID</param>
/// <param name="yourScore">Your score</param>
/// <param name="yourRole">Your role</param>
/// <param name="yourName">Your name</param>
/// <param name="opponentScore">Opponent's score</param>
/// <param name="opponentRole">Opponent's role</param>
/// <param name="opponentName">Opponent's name</param>
WhackAStoodentServer::Messages::EndGameMessage::EndGameMessage(const uuids::uuid& sessionID, std::int64_t yourScore, EPlayerRole yourRole, std::wstring_view yourName, std::int64_t opponentScore, EPlayerRole opponentRole, std::wstring_view opponentName) :
	sessionID(sessionID),
	yourScore(yourScore),
	yourRole(yourRole),
	yourName(yourName),
	opponentScore(opponentScore),
	opponentRole(opponentRole),
	opponentName(opponentName)
{
	// ...
}

/// <summary>
/// Destroys end game message
/// </summary>
WhackAStoodentServer::Messages::EndGameMessage::~EndGameMessage()
{
	// ...
}

/// <summary>
/// Gets the session ID
/// </summary>
/// <param name="result">Result</param>
/// <returns>Session ID</returns>
uuids::uuid& WhackAStoodentServer::Messages::EndGameMessage::GetSessionID(uuids::uuid& result) const
{
	return result = sessionID;
}

/// <summary>
/// Gets your score
/// </summary>
/// <returns>Your score</returns>
std::int64_t WhackAStoodentServer::Messages::EndGameMessage::GetYourScore() const
{
	return yourScore;
}

/// <summary>
/// Gets your role
/// </summary>
/// <returns>Your role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Messages::EndGameMessage::GetYourRole() const
{
	return yourRole;
}

/// <summary>
/// Gets your name
/// </summary>
/// <returns>Your name</returns>
std::wstring_view WhackAStoodentServer::Messages::EndGameMessage::GetYourName() const
{
	return yourName;
}

/// <summary>
/// Gets the opponent's score
/// </summary>
/// <returns>Opponent's score</returns>
std::int64_t WhackAStoodentServer::Messages::EndGameMessage::GetOpponentScore() const
{
	return opponentScore;
}

/// <summary>
/// Gets the opponent's role
/// </summary>
/// <returns>Opponent's role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Messages::EndGameMessage::GetOpponentRole() const
{
	return opponentRole;
}

/// <summary>
/// Gets the opponent's name
/// </summary>
/// <returns>Opponent's name</returns>
std::wstring_view WhackAStoodentServer::Messages::EndGameMessage::GetOpponentName() const
{
	return opponentName;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::EndGameMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::EndGame>::Serialize(result);
	WhackAStoodentServer::UUIDs::SerializeUUID(sessionID, result);
	WhackAStoodentServer::NumericSerializer::SerializeLong(yourScore, result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(yourRole), result);
	WhackAStoodentServer::StringSerializer::SerializeByteSizedString(yourName, result);
	WhackAStoodentServer::NumericSerializer::SerializeLong(opponentScore, result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(opponentRole), result);
	return WhackAStoodentServer::StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
nonstd::span<const std::uint8_t> WhackAStoodentServer::Messages::EndGameMessage::Deserialize(nonstd::span<const std::uint8_t> data)
{
	std::uint8_t your_role;
	std::uint8_t opponent_role;
	nonstd::span<const std::uint8_t> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::EndGame>::Deserialize(data));
	next_bytes = WhackAStoodentServer::UUIDs::DeserializeUUID(next_bytes, sessionID);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeLong(next_bytes, yourScore);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, your_role);
	yourRole = static_cast<WhackAStoodentServer::EPlayerRole>(your_role);
	next_bytes = WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, yourName);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeLong(next_bytes, opponentScore);
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, opponent_role);
	opponentRole = static_cast<WhackAStoodentServer::EPlayerRole>(opponent_role);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}
