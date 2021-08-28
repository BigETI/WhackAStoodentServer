#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <list>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

#include <uuid.h>

#include <Enumerators/EDenyPlayRequestReason.hpp>
#include <Misc/Event.hpp>
#include <Misc/Game.hpp>
#include <Misc/Peer.hpp>
#include <Misc/User.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a lobby
	/// </summary>
	class Lobby
	{
	public:

		/// <summary>
		/// Used to invoke when an user has connected
		/// </summary>
		Event<std::shared_ptr<User>> OnUserConnected;

		/// <summary>
		/// Used to invoke when an user has been disconnected
		/// </summary>
		Event<std::shared_ptr<User>> OnUserDisconnected;

		/// <summary>
		/// Constructs a lobby
		/// </summary>
		Lobby();

		Lobby(const Lobby&) = delete;
		Lobby(Lobby&&) = delete;

		/// <summary>
		/// Destroys lobby
		/// </summary>
		virtual ~Lobby();

		/// <summary>
		/// Is user valid
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user is valid, otherwise "false"</returns>
		virtual bool IsUserValid(std::shared_ptr<User> user) const;

		/// <summary>
		/// Creates a new user
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="userID">User ID</param>
		/// <param name="name">Username</param>
		/// <returns>User</returns>
		virtual std::shared_ptr<User> CreateUser(std::shared_ptr<Peer> peer, const uuids::uuid& userID, std::wstring_view username);

		/// <summary>
		/// Removes specified user
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user has been successfully removed, otherwise "false"</returns>
		virtual bool RemoveUser(std::shared_ptr<User> user);

		/// <summary>
		/// Is peer an user
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <returns>"true" if successful, otherwise "false"</returns>
		virtual bool IsPeerAnUser(std::shared_ptr<Peer> peer) const;

		/// <summary>
		/// Tries to get user from peer
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <returns>"true" if successful, otherwise "false"</returns>
		virtual bool TryGetUserFromPeer(std::shared_ptr<Peer> peer, std::shared_ptr<User>& result) const;

		/// <summary>
		/// Gets user from peer
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <returns>User if successful, otherwise "null"</returns>
		virtual std::shared_ptr<User> GetUserFromPeer(std::shared_ptr<Peer> peer) const;

		/// <summary>
		/// Is user ID occupied
		/// </summary>
		/// <param name="userID">User ID</param>
		/// <returns>"true" if successful, otherwise "false"</returns>
		virtual bool IsUserIDOccupied(const uuids::uuid& userID) const;

		/// <summary>
		/// Tries to get user from user ID
		/// </summary>
		/// <param name="userID">User ID</param>
		/// <returns>"true" if successful, otherwise "false"</returns>
		virtual bool TryGetUserFromUserID(const uuids::uuid& userID, std::shared_ptr<User>& result) const;

		/// <summary>
		/// Gets user from user ID
		/// </summary>
		/// <param name="userID">User ID</param>
		/// <returns>User if successful, otherwise "null"</returns>
		virtual std::shared_ptr<User> GetUserFromUserID(const uuids::uuid& userID) const;

		/// <summary>
		/// Is session code occupied
		/// </summary>
		/// <param name="sessionCode">Sesion code</param>
		/// <returns>"true" if specified session code is associated with an user, otherwise "false"</returns>
		virtual bool IsSessionCodeOccupied(std::string_view sessionCode) const;

		/// <summary>
		/// Tries to get user from the specified session code
		/// </summary>
		/// <param name="sessionCode">Sesion code</param>
		/// <param name="result">Result</param>
		/// <returns>"true" if specified session code is associated with an user, otherwise "false"</returns>
		virtual bool TryGetUserFromSessionCode(std::string_view sessionCode, std::shared_ptr<User>& result) const;

		/// <summary>
		/// Get user from the specified session code
		/// </summary>
		/// <param name="sessionCode">Sesion code</param>
		/// <returns>User if specified session code is associated with an user, otherwise "null"</returns>
		virtual std::shared_ptr<User> GetUserFromSessionCode(std::string_view sessionCode) const;

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
		/// Is user searching for a game
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user is searching for a game, otherwise "false"</returns>
		virtual bool IsUserSearchingForAGame(std::shared_ptr<User> user) const;

		/// <summary>
		/// Requests for playing
		/// </summary>
		/// <param name="issuingUser">Issuing user</param>
		/// <param name="opposingUser">Opposing user</param>
		/// <returns>"true" if request for playing was successful, otherwise "false"</returns>
		virtual bool RequestForPlaying(std::shared_ptr<User> issuingUser, std::shared_ptr<User> opposingUser);

		/// <summary>
		/// Accepts play request for the specified user
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if play request has been successfully accepted, otherwise "false"</returns>
		virtual bool AcceptPlayRequest(std::shared_ptr<User> user);

		/// <summary>
		/// Denies play request for the specified user
		/// </summary>
		/// <param name="user">User</param>
		/// <param name="reason">Reason</param>
		/// <returns>"true" if play request has been successfully denied, otherwise "false"</returns>
		virtual bool DenyPlayRequest(std::shared_ptr<User> user, EDenyPlayRequestReason reason);

		/// <summary>
		/// Is user in a game
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if user is in a game, otherwise "false"</returns>
		virtual bool IsUserInAGame(std::shared_ptr<User> user) const;

		/// <summary>
		/// Tries to get user's game
		/// </summary>
		/// <param name="user">User</param>
		/// <param name="result">Result</param>
		/// <returns>"true" if user is in a game, otherwise "false"</returns>
		virtual bool TryGetUserGame(std::shared_ptr<User> user, std::shared_ptr<Game>& result) const;

		/// <summary>
		/// Gets user's game
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>Game if successful, otherwise "nullptr"</returns>
		virtual std::shared_ptr<Game> GetUserGame(std::shared_ptr<User> user) const;

		/// <summary>
		/// Processes tick
		/// </summary>
		virtual void ProcessTick();

		Lobby& operator=(const Lobby&) = delete;
		Lobby& operator=(Lobby&&) = delete;

	private:

		/// <summary>
		/// Users
		/// </summary>
		std::unordered_map<std::uint16_t, std::shared_ptr<User>> users;

		/// <summary>
		/// User ID to user lookup
		/// </summary>
		std::unordered_map<uuids::uuid, std::shared_ptr<User>> userIDToUserLookup;

		/// <summary>
		/// Session code to user lookup
		/// </summary>
		std::unordered_map<std::string, std::shared_ptr<User>> sessionCodeToUserLookup;

		/// <summary>
		/// Game searching users
		/// </summary>
		std::list<std::shared_ptr<User>> gameSearchingUsers;

		/// <summary>
		/// Users requesting play
		/// </summary>
		std::unordered_map<uuids::uuid, std::tuple<std::shared_ptr<User>, std::shared_ptr<User>, std::chrono::high_resolution_clock::time_point>> usersRequestingPlay;

		/// <summary>
		/// Games
		/// </summary>
		std::unordered_map<uuids::uuid, std::shared_ptr<Game>> games;

		/// <summary>
		/// User ID to game lookup
		/// </summary>
		std::unordered_map<uuids::uuid, std::shared_ptr<Game>> userIDToGameLookup;

		/// <summary>
		/// Random number generator
		/// </summary>
		std::mt19937 random;

		/// <summary>
		/// Denies play request internally
		/// </summary>
		/// <param name="usersRequestingPlayIterator">Users requesting play iterator</param>
		/// <param name="reason">Reason</param>
		void DenyPlayRequestInternal(std::unordered_map<uuids::uuid, std::tuple<std::shared_ptr<User>, std::shared_ptr<User>, std::chrono::high_resolution_clock::time_point>>::iterator usersRequestingPlayIterator, EDenyPlayRequestReason reason);

		/// <summary>
		/// Creates a new game
		/// </summary>
		/// <param name="firstUser">First user</param>
		/// <param name="secondUser">Second user</param>
		void CreateGame(std::shared_ptr<User> firstUser, std::shared_ptr<User> secondUser);
	};
}
