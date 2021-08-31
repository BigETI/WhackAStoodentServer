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
/// <param name="ipAddress">IP address</param>
/// <returns>"true" if IPv4 address is banned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::IsIPAddressBanned(std::string_view ipAddress) const
{
	return bannedIPAddresses.find(std::string(ipAddress)) != bannedIPAddresses.end();
}

/// <summary>
/// Bans the specified IP address
/// </summary>
/// <param name="ipAddress">IP address</param>
/// <returns>"true" if IPv4 address has been successfully banned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::BanIPAddress(std::string_view ipAddress)
{
	std::string ip_address(ipAddress);
	bool ret(WhackAStoodentServer::IPUtilities::IsIPAddressStringValid(ipAddress) && (bannedIPAddresses.find(ip_address) == bannedIPAddresses.end()));
	if (ret)
	{
		bannedIPAddresses.insert(ip_address);
	}
	return ret;
}

/// <summary>
/// Unbans the specififed IP address
/// </summary>
/// <param name="ipv4Address">IP address</param>
/// <returns>"true" if IPv4 address has been successfully unbanned, otherwise "false"</returns>
bool WhackAStoodentServer::Bans::UnbanIPAddress(std::string_view ipAddress)
{
	return !!bannedIPAddresses.erase(std::string(ipAddress));
}

/// <summary>
/// Clears all bans
/// </summary>
void WhackAStoodentServer::Bans::Clear()
{
	bannedIPAddresses.clear();
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
		for (std::string ip_address_string; std::getline(input_file_stream, ip_address_string);)
		{
			if (BanIPAddress(ip_address_string))
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
		std::string banned_ip_address_string;
		for (const std::string& banned_ip_address : bannedIPAddresses)
		{
			output_file_stream << banned_ip_address << std::endl;
		}
	}
	return ret;
}
