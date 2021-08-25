#pragma once

#include <memory>
#include <string>
#include <string_view>

#include <uuid.h>

#include <Misc/Peer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an user
	/// </summary>
	class User
	{
	public:

		/// <summary>
		/// Used to invoke when user has been connected
		/// </summary>
		Event<> OnConnected;

		/// <summary>
		/// Used to invoke when user has been disconnected
		/// </summary>
		Event<> OnDisconnected;

		/// <summary>
		/// Used to invoke when a ping message has been received
		/// </summary>
		Event<std::int32_t> OnPingReceived;

		/// <summary>
		/// Used to invoke when a pong message has been received
		/// </summary>
		Event<std::int32_t> OnPongReceived;

		/// <summary>
		/// Used to invoke when match history has been requested
		/// </summary>
		Event<> OnMatchHistoryRequested;

		User() = delete;
		User(const User&) = delete;
		User(User&&) = delete;

		/// <summary>
		/// Constructs a user
		/// </summary>
		/// <param name="peer">Peer</param>
		/// <param name="userID">User ID</param>
		/// <param name="username">Username</param>
		/// <param name="sessionCode">Session code</param>
		/// <param name="score">Score</param>
		User(std::shared_ptr<Peer> peer, uuids::uuid userID, std::wstring_view username, std::string_view sessionCode, std::int64_t score);

		/// <summary>
		/// Destroys user
		/// </summary>
		virtual ~User();

		/// <summary>
		/// Gets the peer
		/// </summary>
		/// <returns>Peer</returns>
		virtual const Peer& GetPeer() const;

		/// <summary>
		/// Gets the peer
		/// </summary>
		/// <returns>Peer</returns>
		virtual Peer& GetPeer();

		/// <summary>
		/// Gets the user ID
		/// </summary>
		/// <returns>User ID</returns>
		virtual const uuids::uuid& GetUserID() const;

		/// <summary>
		/// Gets the username
		/// </summary>
		/// <returns>Username</returns>
		virtual std::wstring_view GetUsername() const;

		/// <summary>
		/// Sets a new username
		/// </summary>
		/// <param name="newUsername">New username</param>
		virtual void SetUsername(std::wstring_view newUsername);

		/// <summary>
		/// Gets the session code
		/// </summary>
		/// <returns>Session code</returns>
		virtual std::string_view GetSessionCode() const;

		/// <summary>
		/// Sets a new session code
		/// </summary>
		/// <param name="newSessionCode">New session code</param>
		virtual void SetSessionCode(std::string_view newSessionCode);

		/// <summary>
		/// Resets session code
		/// </summary>
		virtual void ResetSessionCode();

		/// <summary>
		/// Gets the score
		/// </summary>
		/// <returns>Score</returns>
		virtual std::int64_t GetScore() const;

		/// <summary>
		/// Sets a new score
		/// </summary>
		/// <param name="newScore">New score</param>
		virtual void SetScore(std::int64_t newScore);

	private:

		/// <summary>
		/// Peer
		/// </summary>
		std::shared_ptr<Peer> peer;

		/// <summary>
		/// User ID
		/// </summary>
		const uuids::uuid userID;

		/// <summary>
		/// Username
		/// </summary>
		std::wstring username;

		/// <summary>
		/// Session code
		/// </summary>
		std::string sessionCode;

		/// <summary>
		/// Score
		/// </summary>
		std::int64_t score;
	};
}
