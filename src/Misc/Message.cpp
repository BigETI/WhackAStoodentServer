#include <stdexcept>

#include <Misc/Message.hpp>

/// <summary>
/// Constructs a message
/// </summary>
/// <param name="data">Message data</param>
WhackAStoodentServer::Message::Message(const std::span<const std::uint8_t> data) : data(data.begin(), data.end())
{
	if (data.size() < static_cast<std::size_t>(1))
	{
		throw std::invalid_argument("Parameter \"data\" is smaller than one.");
	}
}

/// <summary>
/// Gets the message type
/// </summary>
/// <returns>Message type</returns>
WhackAStoodentServer::EMessageType WhackAStoodentServer::Message::GetMessageType() const
{
	return static_cast<WhackAStoodentServer::EMessageType>(data[0]);
}

/// <summary>
/// Gets message data
/// </summary>
/// <returns>Message data</returns>
const std::span<const std::uint8_t> WhackAStoodentServer::Message::GetData() const
{
	return data;
}
