#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

#include <enet.h>
#include <span.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that provides IP utilities
	/// </summary>
	class IPUtilities
	{
	public:
		IPUtilities() = delete;
		IPUtilities(const IPUtilities&) = delete;
		IPUtilities(IPUtilities&&) = delete;
		~IPUtilities() = delete;

		/// <summary>
		/// Is specified IP address string valid
		/// </summary>
		/// <param name="ipAddressString">IP address string</param>
		/// <returns>"true" if specified IP address string is valid, otherwise "false"</returns>
		static bool IsIPAddressStringValid(std::string_view ipAddressString);

		/// <summary>
		/// Parses the specified IP address string
		/// </summary>
		/// <param name="ipAddressString">IP address string</param>
		/// <param name="result">Result</param>
		/// <returns>"true" if specified IP address string is valid, otherwise "false"</returns>
		static bool ParseIPAddressString(std::string_view ipAddressString, ENetAddress& result);

		/// <summary>
		/// Gets the IP address string from the specified ENet address object
		/// </summary>
		/// <param name="enetAddress">ENet address</param>
		/// <param name="result">Result</param>
		/// <returns>IP address string</returns>
		static std::string& GetIPAddressString(const ENetAddress& enetAddress, std::string& result);

		IPUtilities& operator=(const IPUtilities&) = delete;
		IPUtilities& operator=(IPUtilities&&) = delete;
	};
}
