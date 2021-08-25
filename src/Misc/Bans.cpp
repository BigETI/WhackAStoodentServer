#include <fstream>

#include <Misc/Bans.hpp>
#include <Static/IPUtilities.hpp>

/// <summary>
/// Constructs bans
/// </summary>
WhackAStoodentServer::Bans::Bans()
{
	// ...
}

/// <summary>
/// Destroys bans
/// </summary>
WhackAStoodentServer::Bans::~Bans()
{
	// ...
}

/// <summary>
/// Is IPv4 address banned
/// </summary>
/// <param name="ipv4Address">IPv4 address</param>
/// <returns>"true" if IPv4 address is banned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::IsIPAddressBanned(std::uint32_t ipv4Address) const
{
	return bannedIPv4Addresses.contains(ipv4Address);
}

/// <summary>
/// Bans the specified IPv4 address
/// </summary>
/// <param name="ipv4Address">IPv4 address</param>
/// <returns>"true" if IPv4 address has been successfully banned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::BanIPAddress(std::uint32_t ipv4Address)
{
	bool ret((ipv4Address != static_cast<std::uint32_t>(0)) && !bannedIPv4Addresses.contains(ipv4Address));
	if (ret)
	{
		bannedIPv4Addresses.insert(ipv4Address);
	}
	return ret;
}

/// <summary>
/// Unbans the specififed IPv4 address
/// </summary>
/// <param name="ipv4Address">IPv4 address</param>
/// <returns>"true" if IPv4 address has been successfully unbanned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::UnbanIPAddress(std::uint32_t ipv4Address)
{
	return !!bannedIPv4Addresses.erase(ipv4Address);
}

/// <summary>
/// Clears all bans
/// </summary>
void WhackAStoodentServer::Bans::Clear()
{
	bannedIPv4Addresses.clear();
}

/// <summary>
/// Loads bans from specified file
/// </summary>
/// <param name="filePath">File path</param>
/// <returns>"true" if bans have been successfully loaded from file, otherwise "false"</returns>
std::size_t WhackAStoodentServer::Bans::LoadFromFile(std::string_view filePath)
{
	std::size_t ret(static_cast<std::size_t>(0));
	std::ifstream input_file_stream(filePath.data());
	if (input_file_stream.good())
	{
		for (std::string ipv4_address_string; std::getline(input_file_stream, ipv4_address_string);)
		{
			if (BanIPAddress(WhackAStoodentServer::IPUtilities::ParseIPv4AddressString(ipv4_address_string)))
			{
				++ret;
			}
		}
	}
	return ret;
}

/// <summary>
/// Saves bans to file
/// </summary>
/// <param name="filePath">File path</param>
/// <returns>"true" if bans have been successfully saved to file, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::SaveToFile(std::string_view filePath)
{
	bool ret(false);
	std::ofstream output_file_stream(std::string(filePath).c_str());
	if (output_file_stream.good())
	{
		std::string banned_ipv4_address_string;
		for (const auto& banned_ipv4_address : bannedIPv4Addresses)
		{
			output_file_stream << WhackAStoodentServer::IPUtilities::GetIPv4AddressString(banned_ipv4_address, banned_ipv4_address_string) << std::endl;
		}
	}
	return ret;
}
