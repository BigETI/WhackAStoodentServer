#include <stdexcept>

#include <Misc/Message.hpp>

WhackAStoodentServer::Message::Message(const std::vector<std::uint8_t>& data) : data(data)
{
	if (data.size() < static_cast<std::size_t>(1))
	{
		throw std::invalid_argument("\"data\" is smaller than one.");
	}
}

WhackAStoodentServer::Message::Message(std::uint8_t* data, std::size_t size) : data(data, data + size)
{
	if (!data)
	{
		throw std::invalid_argument("\"data\" is null.");
	}
	if (size < static_cast<std::size_t>(1))
	{
		throw std::invalid_argument("\"size\" is smaller than one.");
	}
}

WhackAStoodentServer::EMessageType WhackAStoodentServer::Message::GetMessageType() const
{
	return static_cast<WhackAStoodentServer::EMessageType>(data[0]);
}

std::vector<std::uint8_t>& WhackAStoodentServer::Message::GetData(std::vector<std::uint8_t>& result) const
{
	std::size_t data_size(GetDataSize());
	result.resize(data_size);
	if (data_size)
	{
		std::memcpy(result.data(), data.data() + 1, data.size() - static_cast<std::size_t>(1));
	}
	return result;
}

std::size_t WhackAStoodentServer::Message::GetDataSize() const
{
	return data.size() - static_cast<std::size_t>(1);
}
