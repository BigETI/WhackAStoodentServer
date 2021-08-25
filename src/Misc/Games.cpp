#include <stdexcept>

#include <Misc/Games.hpp>
#include <Static/SessionCodes.hpp>

/// <summary>
/// Constructs a set of games
/// </summary>
WhackAStoodentServer::Games::Games()
{
	// ...
}

/// <summary>
/// Destroys set of games
/// </summary>
WhackAStoodentServer::Games::~Games()
{
	// ...
}

std::shared_ptr<WhackAStoodentServer::User> WhackAStoodentServer::Games::CreateUser(std::shared_ptr<WhackAStoodentServer::Peer> peer, const uuids::uuid& userID, std::wstring_view username)
{
	std::string session_code;
	while (users.contains(SessionCodes::CreateSessionCode(session_code)));
	std::shared_ptr<WhackAStoodentServer::User> ret(std::make_shared<WhackAStoodentServer::User>(peer, userID, username, session_code, 0L));
	users.insert_or_assign(session_code, ret);
	return ret;
}

bool WhackAStoodentServer::Games::RemoveUser(std::shared_ptr<WhackAStoodentServer::User> user)
{
	if (!user)
	{
		throw std::invalid_argument("Parameter \"user\" is null.");
	}
	bool ret(!!users.erase(std::string(user->GetSessionCode())));
	if (ret)
	{
		availableUserIDs.erase(user->GetUserID());
		usersSearching.remove(user);
		searchingUserIDs.erase(user->GetUserID());
		// TODO: Do something with the running game of the specified user.
	}
	return ret;
}

bool WhackAStoodentServer::Games::AddUserToSearch(std::shared_ptr<WhackAStoodentServer::User> user)
{
	bool ret(users.contains(std::string(user->GetSessionCode())) && !searchingUserIDs.contains(user->GetUserID()));
	if (ret)
	{
		usersSearching.push_back(user);
		searchingUserIDs.insert(user->GetUserID());
	}
	return ret;
}

bool WhackAStoodentServer::Games::RemoveUserFromSearch(std::shared_ptr<WhackAStoodentServer::User> user)
{
	bool ret(users.contains(std::string(user->GetSessionCode())) && searchingUserIDs.contains(user->GetUserID()));
	if (ret)
	{
		usersSearching.remove(user);
		searchingUserIDs.erase(user->GetUserID());
	}
	return ret;
}

bool WhackAStoodentServer::Games::RequestForPlaying(std::shared_ptr<WhackAStoodentServer::User> issuingUser, std::shared_ptr<WhackAStoodentServer::User> opposingUser)
{
	// TODO: Implement request for playing with each other.
	return false;
}
