#pragma once

#include <cstdint>
#include <string_view>
#include <unordered_set>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a set of bans
	/// </summary>
	class Bans
	{
	public:

		/// <summary>
		/// Constructs bans
		/// </summary>
		Bans();

		/// <summary>
		/// Destroys bans
		/// </summary>
		virtual ~Bans();

		Bans(const Bans&) = delete;
		Bans(Bans&&) = delete;

		/// <summary>
		/// Is IPv4 address banned
		/// </summary>
		/// <param name="ipv4Address">IPv4 address</param>
		/// <returns>"true" if IPv4 address is banned, otherwise "false"</returns>
		virtual bool IsIPAddressBanned(std::uint32_t ipv4Address) const;

		/// <summary>
		/// Bans the specified IPv4 address
		/// </summary>
		/// <param name="ipv4Address">IPv4 address</param>
		/// <returns>"true" if IPv4 address has been successfully banned, otherwise "false"</returns>
		virtual bool BanIPAddress(std::uint32_t ipv4Address);

		/// <summary>
		/// Unbans the specififed IP address
		/// </summary>
		/// <param name="ipv4Address">IPv4 address</param>
		/// <returns>"true" if IPv4 address has been successfully unbanned, otherwise "false"</returns>
		virtual bool UnbanIPAddress(std::uint32_t ipv4Address);

		/// <summary>
		/// Clears all bans
		/// </summary>
		virtual void Clear();

		/// <summary>
		/// Loads bans from specified file
		/// </summary>
		/// <param name="filePath">File path</param>
		/// <returns>"true" if bans have been successfully loaded from file, otherwise "false"</returns>
		virtual std::size_t LoadFromFile(std::string_view filePath);

		/// <summary>
		/// Saves bans to file
		/// </summary>
		/// <param name="filePath">File path</param>
		/// <returns>"true" if bans have been successfully saved to file, otherwise "false"</returns>
		virtual bool SaveToFile(std::string_view filePath);

		Bans& operator=(const Bans&) = delete;
		Bans& operator=(Bans&&) = delete;

	private:

		/// <summary>
		/// Banned IPv4 addresses
		/// </summary>
		std::unordered_set<std::uint32_t> bannedIPv4Addresses;
	};
}
