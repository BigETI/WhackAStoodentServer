#include <stdexcept>

#include <Messages/AcknowledgeAuthentificationMessage.hpp>
#include <Messages/DenyPlayRequestMessage.hpp>
#include <Messages/ErrorMessage.hpp>
#include <Messages/RequestPlayMessage.hpp>
#include <Messages/StartedGameMessage.hpp>
#include <Misc/Lobby.hpp>
#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>
#include <Static/UUIDs.hpp>

/// <summary>
/// Constructs a lobby
/// </summary>
WhackAStoodentServer::Lobby::Lobby()
{
	// ...
}

/// <summary>
/// Destroys lobby
/// </summary>
WhackAStoodentServer::Lobby::~Lobby()
{
	// ...
}

/// <summary>
/// Is user valid
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user is valid, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsUserValid(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	return user && (users.find(user->GetPeer().GetIncomingPeerID()) != users.end());
}

/// <summary>
/// Creates a new user
/// </summary>
/// <param name="peer">Peer</param>
/// <param name="userID">User ID</param>
/// <param name="name">Username</param>
/// <returns>User</returns>
std::shared_ptr<WhackAStoodentServer::User> WhackAStoodentServer::Lobby::CreateUser(std::shared_ptr<WhackAStoodentServer::Peer> peer, const uuids::uuid& userID, std::wstring_view username)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
	if (userID.is_nil())
	{
		throw std::invalid_argument("Parameter \"userID\" is not a valid UUID.");
	}
	if (userIDToUserLookup.find(userID) != userIDToUserLookup.end())
	{
		std::stringstream error_message;
		error_message << "User ID \"" << userID << "\" is not a valid UUID.";
		throw std::invalid_argument(error_message.str());
	}
	std::string session_code;
	while (sessionCodeToUserLookup.find(SessionCodes::CreateSessionCode(session_code)) != sessionCodeToUserLookup.end());
	std::shared_ptr<WhackAStoodentServer::User> ret(std::make_shared<WhackAStoodentServer::User>(peer, userID, username, session_code, 0L));
	users.insert_or_assign(peer->GetIncomingPeerID(), ret);
	userIDToUserLookup.insert_or_assign(userID, ret);
	sessionCodeToUserLookup.insert_or_assign(session_code, ret);
	ret->OnConnected += [&, ret]()
	{
		OnUserConnected(ret);
	};
	ret->OnDisconnected += [&, ret]()
	{
		OnUserDisconnected(ret);
	};
	peer->SendPeerMessage<WhackAStoodentServer::Messages::AcknowledgeAuthentificationMessage>(userID, session_code, username);
	ret->OnConnected();
	return ret;
}

/// <summary>
/// Removes specified user
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user has been successfully removed, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::RemoveUser(std::shared_ptr<WhackAStoodentServer::User> user)
{
	if (!user)
	{
		throw std::invalid_argument("Parameter \"user\" is null.");
	}
	bool ret(!!users.erase(user->GetPeer().GetIncomingPeerID()));
	if (ret)
	{
		auto user_id_to_game_lookup_iterator(userIDToGameLookup.find(user->GetUserID()));
		if (user_id_to_game_lookup_iterator != userIDToGameLookup.end())
		{
			user_id_to_game_lookup_iterator->second->FinishGame();
		}
		gameSearchingUsers.remove(user);
		sessionCodeToUserLookup.erase(std::string(user->GetSessionCode()));
		userIDToUserLookup.erase(user->GetUserID());
		std::shared_ptr<WhackAStoodentServer::Game> game;
		if (TryGetUserGame(user, game))
		{
			game->FinishGame();
			games.erase(game->GetGameID());
		}
	}
	return ret;
}

/// <summary>
/// Is peer an user
/// </summary>
/// <param name="peer">Peer</param>
/// <returns>"true" if successful, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsPeerAnUser(std::shared_ptr<WhackAStoodentServer::Peer> peer) const
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
	return users.find(peer->GetIncomingPeerID()) != users.end();
}

/// <summary>
/// Tries to get user from peer
/// </summary>
/// <param name="peer">Peer</param>
/// <returns>"true" if successful, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::TryGetUserFromPeer(std::shared_ptr<WhackAStoodentServer::Peer> peer, std::shared_ptr<WhackAStoodentServer::User>& result) const
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
	auto users_iterator(users.find(peer->GetIncomingPeerID()));
	bool ret(users_iterator != users.end());
	result = ret ? users_iterator->second : nullptr;
	return ret;
}

/// <summary>
/// Gets user from peer
/// </summary>
/// <param name="peer">Peer</param>
/// <returns>User if successful, otherwise "null"</returns>
std::shared_ptr<WhackAStoodentServer::User> WhackAStoodentServer::Lobby::GetUserFromPeer(std::shared_ptr<WhackAStoodentServer::Peer> peer) const
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
	auto users_iterator(users.find(peer->GetIncomingPeerID()));
	return(users_iterator == users.end()) ? nullptr : users_iterator->second;
}

/// <summary>
/// Is user ID occupied
/// </summary>
/// <param name="userID">User ID</param>
/// <returns>"true" if successful, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsUserIDOccupied(const uuids::uuid& userID) const
{
	return userIDToUserLookup.find(userID) != userIDToUserLookup.end();
}

/// <summary>
/// Tries to get user from user ID
/// </summary>
/// <param name="userID">User ID</param>
/// <returns>"true" if successful, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::TryGetUserFromUserID(const uuids::uuid& userID, std::shared_ptr<WhackAStoodentServer::User>& result) const
{
	auto user_id_to_user_lookup_iterator(userIDToUserLookup.find(userID));
	bool ret(user_id_to_user_lookup_iterator != userIDToUserLookup.end());
	result = ret ? user_id_to_user_lookup_iterator->second : nullptr;
	return ret;
}

/// <summary>
/// Gets user from user ID
/// </summary>
/// <param name="userID">User ID</param>
/// <returns>User if successful, otherwise "null"</returns>
std::shared_ptr<WhackAStoodentServer::User> WhackAStoodentServer::Lobby::GetUserFromUserID(const uuids::uuid& userID) const
{
	auto user_id_to_user_lookup_iterator(userIDToUserLookup.find(userID));
	return (user_id_to_user_lookup_iterator != userIDToUserLookup.end()) ? user_id_to_user_lookup_iterator->second : nullptr;
}

/// <summary>
/// Is session code occupied
/// </summary>
/// <param name="sessionCode">Sesion code</param>
/// <returns>"true" if specified session code is associated with an user, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsSessionCodeOccupied(std::string_view sessionCode) const
{
	if (!WhackAStoodentServer::SessionCodes::IsSessionCodeValid(sessionCode))
	{
		throw std::invalid_argument("Session code is not valid.");
	}
	return sessionCodeToUserLookup.find(std::string(sessionCode)) != sessionCodeToUserLookup.end();
}

/// <summary>
/// Tries to get user from the specified session code
/// </summary>
/// <param name="sessionCode">Sesion code</param>
/// <param name="result">Result</param>
/// <returns>"true" if specified session code is associated with an user, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::TryGetUserFromSessionCode(std::string_view sessionCode, std::shared_ptr<WhackAStoodentServer::User>& result) const
{
	if (!WhackAStoodentServer::SessionCodes::IsSessionCodeValid(sessionCode))
	{
		throw std::invalid_argument("Session code is not valid.");
	}
	auto session_code_to_user_lookup_iterator(sessionCodeToUserLookup.find(std::string(sessionCode)));
	bool ret(session_code_to_user_lookup_iterator != sessionCodeToUserLookup.end());
	result = ret ? session_code_to_user_lookup_iterator->second : nullptr;
	return ret;
}

/// <summary>
/// Get user from the specified session code
/// </summary>
/// <param name="sessionCode">Sesion code</param>
/// <returns>User if specified session code is associated with an user, otherwise "null"</returns>
std::shared_ptr<WhackAStoodentServer::User> WhackAStoodentServer::Lobby::GetUserFromSessionCode(std::string_view sessionCode) const
{
	if (!WhackAStoodentServer::SessionCodes::IsSessionCodeValid(sessionCode))
	{
		throw std::invalid_argument("Session code is not valid.");
	}
	auto session_code_to_user_lookup_iterator(sessionCodeToUserLookup.find(std::string(sessionCode)));
	return (session_code_to_user_lookup_iterator == sessionCodeToUserLookup.end()) ? nullptr : session_code_to_user_lookup_iterator->second;
}

/// <summary>
/// Adds user to search
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user has been successfully added to search, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::AddUserToSearch(std::shared_ptr<WhackAStoodentServer::User> user)
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	bool ret(!IsUserSearchingForAGame(user));
	if (ret)
	{
		bool is_added_to_search(true);
		for (std::shared_ptr<User> game_searching_user : gameSearchingUsers)
		{
			if ((game_searching_user != user) && !game_searching_user->IsUserBlocked(user) && !user->IsUserBlocked(game_searching_user))
			{
				gameSearchingUsers.remove(game_searching_user);
				gameSearchingUsers.remove(user);
				CreateGame(user, game_searching_user);
				is_added_to_search = false;
				break;
			}
		}
		if (is_added_to_search)
		{
			gameSearchingUsers.push_back(user);
		}
	}
	return ret;
}

/// <summary>
/// Removes user from search
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user has been successfully removed from search, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::RemoveUserFromSearch(std::shared_ptr<WhackAStoodentServer::User> user)
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	bool ret(std::find(gameSearchingUsers.begin(), gameSearchingUsers.end(), user) != gameSearchingUsers.end());
	gameSearchingUsers.remove(user);
	return ret;
}

/// <summary>
/// Is user searching for a game
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user is searching for a game, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsUserSearchingForAGame(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	bool ret(false);
	for (const std::shared_ptr<WhackAStoodentServer::User>& game_searching_user : gameSearchingUsers)
	{
		if (game_searching_user == user)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

/// <summary>
/// Requests for playing
/// </summary>
/// <param name="issuingUser">Issuing user</param>
/// <param name="opposingUser">Opposing user</param>
/// <returns>"true" if request for playing was successful, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::RequestForPlaying(std::shared_ptr<WhackAStoodentServer::User> issuingUser, std::shared_ptr<WhackAStoodentServer::User> opposingUser)
{
	if (!IsUserValid(issuingUser))
	{
		throw std::invalid_argument("Parameter \"issuingUser\" is not valid.");
	}
	if (!IsUserValid(opposingUser))
	{
		throw std::invalid_argument("Parameter \"opposingUser\" is not valid.");
	}
	bool ret(false);
	if (issuingUser == opposingUser)
	{
		issuingUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, L"You can't play with yourself.");
	}
	else
	{
		auto users_requesting_play_iterator(usersRequestingPlay.find(issuingUser->GetUserID()));
		if (users_requesting_play_iterator == usersRequestingPlay.end())
		{
			auto opposing_users_requesting_play_iterator = usersRequestingPlay.find(opposingUser->GetUserID());
			if (opposing_users_requesting_play_iterator == usersRequestingPlay.end())
			{
				usersRequestingPlay.insert_or_assign(issuingUser->GetUserID(), std::make_tuple(issuingUser, opposingUser, std::chrono::high_resolution_clock::now()));
				usersRequestingPlay.insert_or_assign(opposingUser->GetUserID(), std::make_tuple(opposingUser, issuingUser, std::chrono::high_resolution_clock::now()));
				usersRequestingPlay.erase(opposing_users_requesting_play_iterator);
				opposingUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::RequestPlayMessage>(issuingUser->GetSessionCode(), issuingUser->GetUsername());
			}
			else
			{
				DenyPlayRequestInternal(opposing_users_requesting_play_iterator, WhackAStoodentServer::EDenyPlayRequestReason::NotInterested);
			}
		}
		else
		{
			issuingUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::ErrorMessage>(WhackAStoodentServer::EErrorType::InvalidMessageContext, (std::get<static_cast<std::size_t>(1)>(users_requesting_play_iterator->second) == opposingUser) ? L"You have already requested play with the same user." : L"You already have requested play with someone else.");
		}
	}
	return ret;
}

/// <summary>
/// Accepts play request for the specified user
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if play request has been successfully accepted, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::AcceptPlayRequest(std::shared_ptr<WhackAStoodentServer::User> user)
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	auto users_requesting_play_iterator(usersRequestingPlay.find(user->GetUserID()));
	bool ret(users_requesting_play_iterator != usersRequestingPlay.end());
	if (ret)
	{
		std::shared_ptr<WhackAStoodentServer::User> opposing_user(std::get<static_cast<std::size_t>(1)>(users_requesting_play_iterator->second));
		usersRequestingPlay.erase(opposing_user->GetUserID());
		usersRequestingPlay.erase(users_requesting_play_iterator);
		CreateGame(user, opposing_user);
	}
	return ret;
}

/// <summary>
/// Denies play request for the specified user
/// </summary>
/// <param name="user">User</param>
/// <param name="reason">Reason</param>
/// <returns>"true" if play request has been successfully denied, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::DenyPlayRequest(std::shared_ptr<WhackAStoodentServer::User> user, WhackAStoodentServer::EDenyPlayRequestReason reason)
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	auto users_requesting_play_iterator(usersRequestingPlay.find(user->GetUserID()));
	bool ret(users_requesting_play_iterator != usersRequestingPlay.end());
	if (ret)
	{
		DenyPlayRequestInternal(users_requesting_play_iterator, reason);
	}
	return ret;
}

/// <summary>
/// Is user in a game
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if user is in a game, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::IsUserInAGame(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	if (!IsUserValid(user))
	{
		throw std::invalid_argument("Parameter \"user\" is not valid.");
	}
	return userIDToGameLookup.find(user->GetUserID()) != userIDToGameLookup.end();
}

/// <summary>
/// Tries to get user's game
/// </summary>
/// <param name="user">User</param>
/// <param name="result">Result</param>
/// <returns>"true" if user is in a game, otherwise "false"</returns>
bool WhackAStoodentServer::Lobby::TryGetUserGame(std::shared_ptr<WhackAStoodentServer::User> user, std::shared_ptr<WhackAStoodentServer::Game>& result) const
{
	auto user_id_to_game_lookup_iterator(userIDToGameLookup.find(user->GetUserID()));
	bool ret(user_id_to_game_lookup_iterator != userIDToGameLookup.end());
	result = ret ? user_id_to_game_lookup_iterator->second : nullptr;
	return ret;
}

/// <summary>
/// Gets user's game
/// </summary>
/// <param name="user">User</param>
/// <returns>Game if successful, otherwise "nullptr"</returns>
std::shared_ptr<WhackAStoodentServer::Game> WhackAStoodentServer::Lobby::GetUserGame(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	auto user_id_to_game_lookup_iterator(userIDToGameLookup.find(user->GetUserID()));
	return (user_id_to_game_lookup_iterator != userIDToGameLookup.end()) ? user_id_to_game_lookup_iterator->second : nullptr;
}

/// <summary>
/// Processes tick
/// </summary>
void WhackAStoodentServer::Lobby::ProcessTick()
{
	std::unordered_set<uuids::uuid> remove_games;
	std::unordered_map<uuids::uuid, std::tuple<std::shared_ptr<User>, std::shared_ptr<User>, std::chrono::high_resolution_clock::time_point>> remove_users_requesting_play;
	for (auto game : games)
	{
		game.second->ProcessTick();
		if (game.second->IsGameFinished())
		{
			remove_games.insert(game.first);
		}
	}
	for (const auto& remove_game : remove_games)
	{
		games.erase(remove_game);
	}
	for (const auto& users_requesting_play : usersRequestingPlay)
	{
		std::chrono::milliseconds elapsed_time(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - std::get<static_cast<std::size_t>(2)>(users_requesting_play.second)));
		if (elapsed_time >= WhackAStoodentServer::Rules::MaximalWaitForGameRequestTime)
		{
			remove_users_requesting_play.insert_or_assign(users_requesting_play.first, users_requesting_play.second);
		}
	}
	for (const auto& remove_user_requesting_play : remove_users_requesting_play)
	{
		usersRequestingPlay.erase(remove_user_requesting_play.first);
		std::get<static_cast<std::size_t>(0)>(remove_user_requesting_play.second)->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::DenyPlayRequestMessage>(WhackAStoodentServer::EDenyPlayRequestReason::NotInterested);
		std::get<static_cast<std::size_t>(1)>(remove_user_requesting_play.second)->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::DenyPlayRequestMessage>(WhackAStoodentServer::EDenyPlayRequestReason::NotInterested);
	}
}

/// <summary>
/// Denies play request internally
/// </summary>
/// <param name="usersRequestingPlayIterator">Users requesting play iterator</param>
/// <param name="reason">Reason</param>
void WhackAStoodentServer::Lobby::DenyPlayRequestInternal(std::unordered_map<uuids::uuid, std::tuple<std::shared_ptr<WhackAStoodentServer::User>, std::shared_ptr<WhackAStoodentServer::User>, std::chrono::high_resolution_clock::time_point>>::iterator usersRequestingPlayIterator, WhackAStoodentServer::EDenyPlayRequestReason reason)
{
	std::shared_ptr<WhackAStoodentServer::User> user(std::get<static_cast<std::size_t>(0)>(usersRequestingPlayIterator->second));
	usersRequestingPlay.erase(std::get<static_cast<std::size_t>(1)>(usersRequestingPlayIterator->second)->GetUserID());
	usersRequestingPlay.erase(usersRequestingPlayIterator);
	user->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::DenyPlayRequestMessage>(reason);
}

/// <summary>
/// Creates a new game
/// </summary>
/// <param name="firstUser">First user</param>
/// <param name="secondUser">Second user</param>
void WhackAStoodentServer::Lobby::CreateGame(std::shared_ptr<WhackAStoodentServer::User> firstUser, std::shared_ptr<WhackAStoodentServer::User> secondUser)
{
	bool is_swapped(!(random() & 0x1U));
	std::shared_ptr<WhackAStoodentServer::User> hitter_user(is_swapped ? secondUser : firstUser);
	std::shared_ptr<WhackAStoodentServer::User> mole_user(is_swapped ? firstUser : secondUser);
	uuids::uuid game_id;
	while (games.find(WhackAStoodentServer::UUIDs::CreateNewUUID(game_id)) != games.end());
	std::shared_ptr<WhackAStoodentServer::Game> game(std::make_shared<WhackAStoodentServer::Game>(game_id, hitter_user, mole_user));
	game->OnGameFinished += [&, game, hitter_user, mole_user]()
	{
		userIDToGameLookup.erase(hitter_user->GetUserID());
		userIDToGameLookup.erase(mole_user->GetUserID());
	};
	games.insert_or_assign(game_id, game);
	userIDToGameLookup.insert_or_assign(hitter_user->GetUserID(), game);
	userIDToGameLookup.insert_or_assign(mole_user->GetUserID(), game);
	hitter_user->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::StartedGameMessage>(WhackAStoodentServer::EPlayerRole::Hitter, mole_user->GetUsername());
	mole_user->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::StartedGameMessage>(WhackAStoodentServer::EPlayerRole::Mole, hitter_user->GetUsername());
}
