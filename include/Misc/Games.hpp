#pragma once

#include <memory>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include <uuid.h>

#include <Misc/Peer.hpp>
#include <Misc/User.hpp>

namespace WhackAStoodentServer
{
	class Games
	{
	public:

		Games();

		Games(const Games&) = delete;
		Games(Games&&) = delete;

		virtual std::shared_ptr<User> CreateUser(std::shared_ptr<Peer> peer, const uuids::uuid& userID, const std::wstring& name);

		virtual bool RemoveUser(std::shared_ptr<User> user);

		virtual bool AddUserToSearch(std::shared_ptr<User> user);

		virtual bool RemoveUserFromSearch(std::shared_ptr<User> user);

		virtual bool RequestForPlaying(std::shared_ptr<User> issuingUser, std::shared_ptr<User> opposingUser);

		Games& operator=(const Games&) = delete;
		Games& operator=(Games&&) = delete;

	private:

		std::unordered_map<std::string, std::shared_ptr<User>> users;

		std::unordered_set<uuids::uuid> availableUserIDs;

		std::list<std::shared_ptr<User>> usersSearching;

		std::unordered_set<uuids::uuid> searchingUserIDs;

		std::unordered_map<uuids::uuid, std::pair<std::shared_ptr<User>, std::shared_ptr<User>>> usersRequestingPlay;
	};
}
