#include <stdexcept>

#include <Misc/User.hpp>
#include <Static/SessionCodes.hpp>

WhackAStoodentServer::User::User(std::shared_ptr<Peer> peer, uuids::uuid userID, const std::wstring& name, const std::string& sessionCode, int64_t score) :
	peer(peer),
	userID(userID),
	name(name),
	sessionCode(sessionCode),
	score(score)
{
	if (!peer)
	{
		throw std::invalid_argument("Parameter \"peer\" is null.");
	}
}

WhackAStoodentServer::User::~User()
{
	// ...
}

const WhackAStoodentServer::Peer& WhackAStoodentServer::User::GetPeer() const
{
	return *peer;
}

WhackAStoodentServer::Peer& WhackAStoodentServer::User::GetPeer()
{
	return *peer;
}

const uuids::uuid& WhackAStoodentServer::User::GetUserID() const
{
	return userID;
}

const std::wstring& WhackAStoodentServer::User::GetName() const
{
	return name;
}

void WhackAStoodentServer::User::SetName(const std::wstring& newName)
{
	name = newName;
}

const std::string& WhackAStoodentServer::User::GetSessionCode() const
{
	return sessionCode;
}

void WhackAStoodentServer::User::SetSessionCode(const std::string& newSessionCode)
{
	if (!SessionCodes::IsSessionCodeValid(newSessionCode))
	{
		throw std::invalid_argument("Parameter \"newSessionCode\" is not valid.");
	}
	sessionCode = newSessionCode;
}

void WhackAStoodentServer::User::SetSessionCode(std::string&& newSessionCode)
{
	if (!SessionCodes::IsSessionCodeValid(newSessionCode))
	{
		throw std::invalid_argument("Parameter \"newSessionCode\" is not valid.");
	}
	sessionCode = newSessionCode;
}

void WhackAStoodentServer::User::ResetSessionCode()
{
	sessionCode.clear();
}

std::int64_t WhackAStoodentServer::User::GetScore() const
{
	return score;
}

void WhackAStoodentServer::User::SetScore(std::int64_t newScore)
{
	score = newScore;
}
