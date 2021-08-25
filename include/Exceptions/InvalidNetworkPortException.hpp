#pragma once

#include <cstdint>
#include <stdexcept>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an invalid network port exception
	/// </summary>
	class InvalidNetworkPortException : public std::runtime_error
	{
	public:

		InvalidNetworkPortException() = delete;

		/// <summary>
		/// Constructs an invalid network port exception
		/// </summary>
		/// <param name="port">Network port</param>
		InvalidNetworkPortException(std::uint16_t port);

		/// <summary>
		/// Destroys invalid network port exception
		/// </summary>
		virtual ~InvalidNetworkPortException() override;

		/// <summary>
		/// Gets the network port
		/// </summary>
		/// <returns>Network port</returns>
		virtual std::uint16_t GetPort() const;

	private:

		/// <summary>
		/// Network port
		/// </summary>
		std::uint16_t port;
	};
}
