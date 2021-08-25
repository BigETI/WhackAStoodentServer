#pragma once

#include <memory>
#include <list>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <uuid.h>

#include <Misc/Peer.hpp>
#include <Misc/User.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a set of games
	/// </summary>
	class Games
	{
	public:

		/// <summary>
		/// Constructs a set of games
		/// </summary>
		Games();

		Games(const Games&) = delete;
		Games(Games&&) = delete;

		/// <summary>
		/// Destroys set of games
		/// </summary>
		virtual ~Games();

		/// <summary>
		/// Creates a new user
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="userID">User ID</param>
		/// <param name="name">Username</param>
		/// <returns></returns>
		virtual std::shared_ptr<User> CreateUser(std::shared_ptr<Peer> peer, const uuids::uuid& userID, std::wstring_view username);

		/// <summary>
		/// Removes specified user
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user has been successfully removed, otherwise "false"</returns>
		virtual bool RemoveUser(std::shared_ptr<User> user);

		/// <summary>
		/// Adds user to search
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user has been successfully added to search, otherwise "false"</returns>
		virtual bool AddUserToSearch(std::shared_ptr<User> user);

		/// <summary>
		/// Removes user from search
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user has been successfully removed from search, otherwise "false"</returns>
		virtual bool RemoveUserFromSearch(std::shared_ptr<User> user);

		/// <summary>
		/// Requests for playing
		/// </summary>
		/// <param name="issuingUser">Issuing user</param>
		/// <param name="opposingUser">Opposing user</param>
		/// <returns>"true" if request for playing was successful, otherwise "false"</returns>
		virtual bool RequestForPlaying(std::shared_ptr<User> issuingUser, std::shared_ptr<User> opposingUser);

		Games& operator=(const Games&) = delete;
		Games& operator=(Games&&) = delete;

	private:

		/// <summary>
		/// Users
		/// </summary>
		std::unordered_map<std::string, std::shared_ptr<User>> users;

		/// <summary>
		/// Available user IDs
		/// </summary>
		std::unordered_set<uuids::uuid> availableUserIDs;

		/// <summary>
		/// Users searching
		/// </summary>
		std::list<std::shared_ptr<User>> usersSearching;

		/// <summary>
		/// Searching user IDs
		/// </summary>
		std::unordered_set<uuids::uuid> searchingUserIDs;

		/// <summary>
		/// Users requesting play
		/// </summary>
		std::unordered_map<uuids::uuid, std::pair<std::shared_ptr<User>, std::shared_ptr<User>>> usersRequestingPlay;
	};
}
