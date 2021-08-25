#include <string>

#include <Exceptions/InvalidNetworkPortException.hpp>

/// <summary>
/// Constructs an invalid network port exception
/// </summary>
/// <param name="port">Network port</param>
WhackAStoodentServer::InvalidNetworkPortException::InvalidNetworkPortException(std::uint16_t port) :
	std::runtime_error("Invalid network port \"" + std::to_string(port) + "\" has been specified."),
	port(port)
{
	// ...
}

/// <summary>
/// Destroys invalid network port exception
/// </summary>
WhackAStoodentServer::InvalidNetworkPortException::~InvalidNetworkPortException()
{
	// ...
}

/// <summary>
/// Gets the network port
/// </summary>
/// <returns>Network port</returns>
std::uint16_t WhackAStoodentServer::InvalidNetworkPortException::GetPort() const
{
	return port;
}
