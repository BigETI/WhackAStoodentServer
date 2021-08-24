#include <vector>

#include <Static/IPUtilities.hpp>
#include <Static/StringUtilities.hpp>

/// <summary>
/// Is IPv4 address valid
/// </summary>
/// <param name="ipv4Address">IPv4 address</param>
/// <param name="result">Result</param>
/// <returns>"true" if IPv4 address is valid, otherwise "false"</returns>
bool WhackAStoodentServer::IPUtilities::IsIPv4AddressValid(std::uint32_t ipv4Address, std::array<std::uint8_t, sizeof(std::uint32_t)>* result)
{
	std::array<std::uint8_t, sizeof(std::uint32_t)> numeric_parts
	{
		static_cast<std::uint8_t>((ipv4Address >> static_cast<std::uint32_t>(24)) & static_cast<std::uint32_t>(0xFF)),
		static_cast<std::uint8_t>((ipv4Address >> static_cast<std::uint32_t>(16)) & static_cast<std::uint32_t>(0xFF)),
		static_cast<std::uint8_t>((ipv4Address >> static_cast<std::uint32_t>(8)) & static_cast<std::uint32_t>(0xFF)),
		static_cast<std::uint8_t>(ipv4Address & static_cast<std::uint32_t>(0xFF))
	};
	bool ret((numeric_parts[0] > 0x00) && (numeric_parts[0] <= 0xFF) &&
		(numeric_parts[1] >= 0x00) && (numeric_parts[1] <= 0xFF) &&
		(numeric_parts[2] >= 0x00) && (numeric_parts[2] <= 0xFF) &&
		(numeric_parts[3] > 0x00) && (numeric_parts[3] <= 0xFF));
	if (ret && result)
	{
		*result = numeric_parts;
	}
	return ret;
}

/// <summary>
/// Parses IPv4 address string
/// </summary>
/// <param name="ipv4AddressString">IPv4 address string</param>
/// <returns>IPv4 address</returns>
std::uint32_t WhackAStoodentServer::IPUtilities::ParseIPv4AddressString(std::string_view ipv4AddressString)
{
	std::uint32_t ret(static_cast<std::uint32_t>(0));
	std::vector<std::string> parts;
	if (WhackAStoodentServer::StringUtilities::SplitString(ipv4AddressString, ".", parts).size() == sizeof(std::uint32_t))
	{
		std::array<int, sizeof(std::uint32_t)> numeric_parts
		{
			std::atoi(parts[0].c_str()),
			std::atoi(parts[1].c_str()),
			std::atoi(parts[2].c_str()),
			std::atoi(parts[3].c_str())
		};
		if ((numeric_parts[0] > 0x00) && (numeric_parts[0] <= 0xFF) &&
			(numeric_parts[1] >= 0x00) && (numeric_parts[1] <= 0xFF) &&
			(numeric_parts[2] >= 0x00) && (numeric_parts[2] <= 0xFF) &&
			(numeric_parts[3] > 0x00) && (numeric_parts[3] <= 0xFF))
		{
			ret = (numeric_parts[3] << 24) | (numeric_parts[2] << 16) | (numeric_parts[1] << 8) | numeric_parts[0];
		}
	}
	return ret;
}

/// <summary>
/// Gets IPv4 address
/// </summary>
/// <param name="ipv4Address">IPv4 address</param>
/// <param name="result">Result</param>
/// <returns>IPv4 address string</returns>
std::string& WhackAStoodentServer::IPUtilities::GetIPv4AddressString(std::uint32_t ipv4Address, std::string& result)
{
	result.clear();
	std::array<std::uint8_t, sizeof(std::uint32_t)> numeric_parts;
	if (IsIPv4AddressValid(ipv4Address, &numeric_parts))
	{
		result = std::to_string(numeric_parts[3]) + '.' + std::to_string(numeric_parts[2]) + '.' + std::to_string(numeric_parts[1]) + '.' + std::to_string(numeric_parts[0]);
	}
	return result;
}
