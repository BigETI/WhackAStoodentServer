#include <Messages/DenyPlayRequestMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Constructs a deny play request message
/// </summary>
WhackAStoodentServer::Messages::DenyPlayRequestMessage::DenyPlayRequestMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>(),
	reason(WhackAStoodentServer::EDenyPlayRequestReason::NoReason)
{
	// ...
}

/// <summary>
/// Constructs a deny play request message
/// </summary>
/// <param name="reason">Reason</param>
WhackAStoodentServer::Messages::DenyPlayRequestMessage::DenyPlayRequestMessage(WhackAStoodentServer::EDenyPlayRequestReason reason) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>(),
	reason(reason)
{
	// ...
}

/// <summary>
/// Destroys deny play request message
/// </summary>
WhackAStoodentServer::Messages::DenyPlayRequestMessage::~DenyPlayRequestMessage()
{
	// ...
}

/// <summary>
/// Gets the deny play request reason
/// </summary>
/// <returns>Deny play request reason</returns>
WhackAStoodentServer::EDenyPlayRequestReason WhackAStoodentServer::Messages::DenyPlayRequestMessage::GetReason() const
{
	return reason;
}

/// <summary>
/// Serializes contents
/// </summary>
/// <param name="result">Result</param>
/// <returns>Serialized contents</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::Messages::DenyPlayRequestMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>::Serialize(result);
	return NumericSerializer::SerializeByte(static_cast<std::uint8_t>(reason), result);
}

/// <summary>
/// Deserializes given input
/// </summary>
/// <param name="data">Data to deserialize</param>
/// <returns>Remaining data to deserialize</returns>
std::span<std::uint8_t const> WhackAStoodentServer::Messages::DenyPlayRequestMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> ret(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>::Deserialize(data));
	std::uint8_t reason_id;
	ret = NumericSerializer::DeserializeByte(ret, reason_id);
	reason = static_cast<WhackAStoodentServer::EDenyPlayRequestReason>(reason_id);
	return ret;
}
