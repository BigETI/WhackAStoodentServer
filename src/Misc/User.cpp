#include <stdexcept>

#include <Misc/User.hpp>

WhackAStoodentServer::User::User(std::shared_ptr<Peer> peer, uuids::uuid userID, const std::wstring& name, int64_t score) :
	peer(peer),
	userID(userID),
	name(name),
	score(score)
{
	if (!peer)
	{
		throw std::invalid_argument("\"peer\" is null.");
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

std::int64_t WhackAStoodentServer::User::GetScore() const
{
	return score;
}

void WhackAStoodentServer::User::SetScore(std::int64_t newScore)
{
	score = newScore;
}
