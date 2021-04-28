#include <string>

#include <Exceptions/InvalidNetworkPortException.hpp>

WhackAStoodentServer::InvalidNetworkPortException::InvalidNetworkPortException(std::uint16_t port) :
	std::runtime_error("Invalid network port \"" + std::to_string(port) + "\" has been specified."),
	port(port)
{
	// ...
}

WhackAStoodentServer::InvalidNetworkPortException::~InvalidNetworkPortException()
{
	// ...
}

std::uint16_t WhackAStoodentServer::InvalidNetworkPortException::GetPort() const
{
	return port;
}
