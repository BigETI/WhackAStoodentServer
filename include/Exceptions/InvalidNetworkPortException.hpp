#pragma once

#include <cstdint>
#include <stdexcept>

namespace WhackAStoodentServer
{
	class InvalidNetworkPortException : public std::runtime_error
	{
	public:

		InvalidNetworkPortException() = delete;

		InvalidNetworkPortException(std::uint16_t port);

		virtual ~InvalidNetworkPortException();

		virtual std::uint16_t GetPort() const;

	private:

		std::uint16_t port;
	};
}