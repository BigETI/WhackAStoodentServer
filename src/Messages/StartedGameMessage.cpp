#include <Messages/StartedGameMessage.hpp>
#include <Static/NumericSerializer.hpp>
#include <Static/StringSerializer.hpp>

/// <summary>
/// Constructs a started game message
/// </summary>
WhackAStoodentServer::Messages::StartedGameMessage::StartedGameMessage() :
	yourRole(WhackAStoodentServer::EPlayerRole::Hitter)
{
	// ...
}

/// <summary>
/// Constructs a started game message
/// </summary>
/// <param name="opponentSessionCode">Opponent's session code</param>
/// <param name="opponentName">Opponent's name</param>
WhackAStoodentServer::Messages::StartedGameMessage::StartedGameMessage(WhackAStoodentServer::EPlayerRole yourRole, std::wstring_view opponentName) :
	yourRole(yourRole),
	opponentName(opponentName)
{
	// ...
}

/// <summary>
/// Destroys started game message
/// </summary>
WhackAStoodentServer::Messages::StartedGameMessage::~StartedGameMessage()
{
	// ...
}

/// <summary>
/// Gets your role
/// </summary>
/// <returns>Your role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Messages::StartedGameMessage::GetYourRole() const
{
	return yourRole;
}

/// <summary>
/// Gets the opponent's name
/// </summary>
/// <returns>Opponent's name</returns>
std::wstring_view WhackAStoodentServer::Messages::StartedGameMessage::GetOpponentName() const
{
	return opponentName;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::StartedGameMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::StartedGame>::Serialize(result);
	WhackAStoodentServer::NumericSerializer::SerializeByte(static_cast<std::uint8_t>(yourRole), result);
	return WhackAStoodentServer::StringSerializer::SerializeByteSizedString(opponentName, result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::StartedGameMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::uint8_t your_role;
	std::span<std::uint8_t const> next_bytes(WhackAStoodentServer::Messages::ASerializableMessage<WhackAStoodentServer::EMessageType::StartedGame>::Deserialize(data));
	next_bytes = WhackAStoodentServer::NumericSerializer::DeserializeByte(next_bytes, your_role);
	yourRole = static_cast<WhackAStoodentServer::EPlayerRole>(your_role);
	return WhackAStoodentServer::StringSerializer::DeserializeByteSizedString(next_bytes, opponentName);
}
