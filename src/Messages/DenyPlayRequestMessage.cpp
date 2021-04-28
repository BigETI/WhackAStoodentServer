#include <Messages/DenyPlayRequestMessage.hpp>
#include <Static/NumericSerializer.hpp>

WhackAStoodentServer::Messages::DenyPlayRequestMessage::DenyPlayRequestMessage() :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>(),
	reason(WhackAStoodentServer::EDenyPlayRequestReason::NoReason)
{
	// ...
}

WhackAStoodentServer::Messages::DenyPlayRequestMessage::DenyPlayRequestMessage(WhackAStoodentServer::EDenyPlayRequestReason reason) :
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>(),
	reason(reason)
{
	// ...
}

WhackAStoodentServer::Messages::DenyPlayRequestMessage::~DenyPlayRequestMessage()
{
	// ...
}

WhackAStoodentServer::EDenyPlayRequestReason WhackAStoodentServer::Messages::DenyPlayRequestMessage::GetReason() const
{
	return reason;
}

std::vector<std::uint8_t>& WhackAStoodentServer::Messages::DenyPlayRequestMessage::Serialize(std::vector<std::uint8_t>& result) const
{
	WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>::Serialize(result);
	return NumericSerializer::SerializeByte(static_cast<std::uint8_t>(reason), result);
}

std::span<std::uint8_t const> WhackAStoodentServer::Messages::DenyPlayRequestMessage::Deserialize(const std::span<std::uint8_t const>& data)
{
	std::span<std::uint8_t const> ret(WhackAStoodentServer::Messages::ASerializableMessage<EMessageType::DenyPlayRequest>::Deserialize(data));
	std::uint8_t reason_id;
	ret = NumericSerializer::DeserializeByte(ret, reason_id);
	reason = static_cast<WhackAStoodentServer::EDenyPlayRequestReason>(reason_id);
	return ret;
}
