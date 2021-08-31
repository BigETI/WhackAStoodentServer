#include <vector>

#include <string.h>

#include <Static/IPUtilities.hpp>
#include <Static/StringUtilities.hpp>

/// <summary>
/// Is specified IP address string valid
/// </summary>
/// <param name="ipAddressString">IP address string</param>
/// <returns>"true" if specified IP address string is valid, otherwise "false"</returns>
bool WhackAStoodentServer::IPUtilities::IsIPAddressStringValid(std::string_view ipAddressString)
{
	ENetAddress enet_address;
	std::string ip_address_string(ipAddressString);
	return enet_address_set_ip(&enet_address, ip_address_string.c_str()) == 0;
}

/// <summary>
/// Parses the specified IP address string
/// </summary>
/// <param name="ipAddressString">IP address string</param>
/// <param name="result">Result</param>
/// <returns>"true" if specified IP address string is valid, otherwise "false"</returns>
bool WhackAStoodentServer::IPUtilities::ParseIPAddressString(std::string_view ipAddressString, ENetAddress& result)
{
	std::string ip_address_string(ipAddressString);
	return enet_address_set_ip(&result, ip_address_string.c_str()) == 0;
}

/// <summary>
/// Gets the IP address string from the specified ENet address object
/// </summary>
/// <param name="enetAddress">ENet address</param>
/// <param name="result">Result</param>
/// <returns>IP address string</returns>
std::string& WhackAStoodentServer::IPUtilities::GetIPAddressString(const ENetAddress& enetAddress, std::string& result)
{
	result.resize(static_cast<std::size_t>(45));
	if (enet_address_get_ip(&enetAddress, result.data(), result.length()) == 0)
	{
		result.resize(strlen(result.c_str()));
	}
	else
	{
		result.clear();
	}
	return result;
}
