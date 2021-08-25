#include <stdexcept>

#include <Misc/User.hpp>
#include <Static/SessionCodes.hpp>

/// <summary>
/// Constructs a user
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="userID">User ID</param>
/// <param name="username">Username</param>
/// <param name="sessionCode">Session code</param>
/// <param name="score">Score</param>
WhackAStoodentServer::User::User(std::shared_ptr<Peer> peer, uuids::uuid userID, std::wstring_view username, std::string_view sessionCode, int64_t score) :
	peer(peer),
	userID(userID),
	username(username),
	sessionCode(sessionCode),
	score(score)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
}

/// <summary>
/// Destroys user
/// </summary>
WhackAStoodentServer::User::~User()
{
	// ...
}

/// <summary>
/// Gets the peer
/// </summary>
/// <returns>Peer</returns>
const WhackAStoodentServer::Peer& WhackAStoodentServer::User::GetPeer() const
{
	return *peer;
}

/// <summary>
/// Gets the peer
/// </summary>
/// <returns>Peer</returns>
WhackAStoodentServer::Peer& WhackAStoodentServer::User::GetPeer()
{
	return *peer;
}

/// <summary>
/// Gets the user ID
/// </summary>
/// <returns>User ID</returns>
const uuids::uuid& WhackAStoodentServer::User::GetUserID() const
{
	return userID;
}

/// <summary>
/// Gets the username
/// </summary>
/// <returns>Username</returns>
std::wstring_view WhackAStoodentServer::User::GetUsername() const
{
	return username;
}

/// <summary>
/// Sets a new username
/// </summary>
/// <param name="newUsername">New username</param>
void WhackAStoodentServer::User::SetUsername(std::wstring_view newUsername)
{
	username = newUsername;
}

/// <summary>
/// Gets the session code
/// </summary>
/// <returns>Session code</returns>
std::string_view WhackAStoodentServer::User::GetSessionCode() const
{
	return sessionCode;
}

/// <summary>
/// Sets a new session code
/// </summary>
/// <param name="newSessionCode">New session code</param>
void WhackAStoodentServer::User::SetSessionCode(std::string_view newSessionCode)
{
	if (!SessionCodes::IsSessionCodeValid(newSessionCode))
	{
		throw std::invalid_argument("Parameter \"newSessionCode\" is not valid.");
	}
	sessionCode = newSessionCode;
}

/// <summary>
/// Resets session code
/// </summary>
void WhackAStoodentServer::User::ResetSessionCode()
{
	sessionCode.clear();
}

/// <summary>
/// Gets the score
/// </summary>
/// <returns>Score</returns>
std::int64_t WhackAStoodentServer::User::GetScore() const
{
	return score;
}

/// <summary>
/// Sets a new score
/// </summary>
/// <param name="newScore">New score</param>
void WhackAStoodentServer::User::SetScore(std::int64_t newScore)
{
	score = newScore;
}
