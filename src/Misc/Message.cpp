#include <stdexcept>

#include <Misc/Message.hpp>

WhackAStoodentServer::Message::Message(const std::vector<std::uint8_t>& data, std::shared_ptr<WhackAStoodentServer::Peer> peer) : data(data), peer(peer)
{
	if (data.size() < static_cast<std::size_t>(1))
	{
		throw std::invalid_argument("\"data\" is smaller than one.");
	}
	if (!peer)
	{
		throw std::invalid_argument("\"peer\" is null.");
	}
}

WhackAStoodentServer::Message::Message(std::uint8_t* data, std::size_t size, std::shared_ptr<WhackAStoodentServer::Peer> peer) : data(data, data + size), peer(peer)
{
	if (!data)
	{
		throw std::invalid_argument("\"data\" is null.");
	}
	if (size < static_cast<std::size_t>(1))
	{
		throw std::invalid_argument("\"size\" is smaller than one.");
	}
	if (!peer)
	{
		throw std::invalid_argument("\"peer\" is null.");
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

const WhackAStoodentServer::Peer& WhackAStoodentServer::Message::GetPeer() const
{
	return *peer;
}

WhackAStoodentServer::Peer& WhackAStoodentServer::Message::GetPeer()
{
	return *peer;
}
