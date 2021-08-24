#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>

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
		/// Is IPv4 address valid
		/// </summary>
		/// <param name="ipv4Address">IPv4 address</param>
		/// <param name="result">Result</param>
		/// <returns>"true" if IPv4 address is valid, otherwise "false"</returns>
		static bool IsIPv4AddressValid(std::uint32_t ipv4Address, std::array<std::uint8_t, sizeof(std::uint32_t)>* result = nullptr);

		/// <summary>
		/// Parses IPv4 address string
		/// </summary>
		/// <param name="ipv4AddressString">IPv4 address string</param>
		/// <returns>IPv4 address</returns>
		static std::uint32_t ParseIPv4AddressString(std::string_view ipv4AddressString);

		/// <summary>
		/// Gets IPv4 address
		/// </summary>
		/// <param name="ipv4Address">IPv4 address</param>
		/// <param name="result">Result</param>
		/// <returns>IPv4 address string</returns>
		static std::string& GetIPv4AddressString(std::uint32_t ipv4Address, std::string& result);

		IPUtilities& operator=(const IPUtilities&) = delete;
		IPUtilities& operator=(IPUtilities&&) = delete;
	};
}
