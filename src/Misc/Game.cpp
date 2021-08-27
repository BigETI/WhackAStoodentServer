#include <Messages/HideMessage.hpp>
#include <Messages/HitFailMessage.hpp>
#include <Messages/HitSuccessMessage.hpp>
#include <Messages/LookMessage.hpp>
#include <Misc/Game.hpp>
#include <Static/Rules.hpp>

const std::array<const WhackAStoodentServer::Hole, 4ULL> WhackAStoodentServer::Game::Holes =
{
	WhackAStoodentServer::Hole(WhackAStoodentServer::Vector2D<float>(-4.627595f, -2.85f), WhackAStoodentServer::Vector2D<float>(4.11071f, 2.26f)),
	WhackAStoodentServer::Hole(WhackAStoodentServer::Vector2D<float>(4.862405f, -2.85f), WhackAStoodentServer::Vector2D<float>(4.11071f, 2.26f)),
	WhackAStoodentServer::Hole(WhackAStoodentServer::Vector2D<float>(4.862405f, -12.9f), WhackAStoodentServer::Vector2D<float>(4.11071f, 2.3f)),
	WhackAStoodentServer::Hole(WhackAStoodentServer::Vector2D<float>(-4.577595f, -12.9f), WhackAStoodentServer::Vector2D<float>(4.11071f, 2.3f))
};

/// <summary>
/// Constructs a game
/// </summary>
/// <param name="hitterUser">User (hitter)(</param>
/// <param name="moleUser">User (mole)(</param>
WhackAStoodentServer::Game::Game(std::shared_ptr<WhackAStoodentServer::User> hitterUser, std::shared_ptr<WhackAStoodentServer::User> moleUser) :
	hitterUser(std::make_pair(hitterUser, false)),
	moleUser(std::make_pair(moleUser, false)),
	isGameRunning(false),
	gameStartedTimePoint(std::chrono::high_resolution_clock::now()),
	lookingHoleIndex(-1)
{
	if (!hitterUser)
	{
		throw std::invalid_argument("Parameter \"hitterUser\" is null.");
	}
	if (!moleUser)
	{
		throw std::invalid_argument("Parameter \"moleUser\" is null.");
	}
	if (hitterUser == moleUser)
	{
		throw std::invalid_argument("Hitter is the same as mole.");
	}
}

/// <summary>
/// Destroys game
/// </summary>
WhackAStoodentServer::Game::~Game()
{
	// ...
}

/// <summary>
/// Is game loaded
/// </summary>
/// <param name="role">Role</param>
bool WhackAStoodentServer::Game::IsGameLoaded(WhackAStoodentServer::EPlayerRole role) const
{
	return (role == WhackAStoodentServer::EPlayerRole::Hitter) ? hitterUser.second : moleUser.second;
}

/// <summary>
/// Is game loaded for user
/// </summary>
/// <param name="user">User</param>
bool WhackAStoodentServer::Game::IsGameLoadedForUser(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	return IsGameLoaded(GetPlayerRole(user));
}

/// <summary>
/// Are games loaded
/// </summary>
bool WhackAStoodentServer::Game::AreGamesLoaded() const
{
	return hitterUser.second && moleUser.second;
}

/// <summary>
/// Is game running
/// </summary>
bool WhackAStoodentServer::Game::IsGameRunning() const
{
	return isGameRunning;
}

/// <summary>
/// Starts game
/// </summary>
/// <returns>"true" if game has been successfully started, otherwise "false"</returns>
bool WhackAStoodentServer::Game::StartGame()
{
	bool ret(!isGameRunning && AreGamesLoaded());
	if (ret)
	{
		gameStartedTimePoint = std::chrono::high_resolution_clock::now();
		isGameRunning = true;
		OnGameStarted();
	}
	return ret;
}

/// <summary>
/// Stops game
/// </summary>
bool WhackAStoodentServer::Game::StopGame()
{
	bool ret(isGameRunning);
	if (ret)
	{
		isGameRunning = false;
		OnGameStopped();
	}
	return ret;
}

/// <summary>
/// Gets player role
/// </summary>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Game::GetPlayerRole(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	if (!user)
	{
		throw std::invalid_argument("Parameter \"user\" is null.");
	}
	WhackAStoodentServer::EPlayerRole ret;
	if (user == hitterUser.first)
	{
		ret = WhackAStoodentServer::EPlayerRole::Hitter;
	}
	else if (user == moleUser.first)
	{
		ret = WhackAStoodentServer::EPlayerRole::Mole;
	}
	else
	{
		throw std::invalid_argument("Specified user is not in this game.");
	}
	return ret;
}

/// <summary>
/// Hits at the given position
/// </summary>
/// <param name="position">Position</param>
/// <returns>"true" if hitting was successful, otherwise "false"</returns>
bool WhackAStoodentServer::Game::Hit(const WhackAStoodentServer::Vector2D<float>& position)
{
	bool ret((lookingHoleIndex >= 0) && Holes[lookingHoleIndex].IsPositionInHole(position));
	if (ret)
	{
		std::int64_t new_score(hitterUser.first->GetScore() + WhackAStoodentServer::Rules::HittingScore);
		hitterUser.first->SetScore(new_score);
		hitterUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitSuccessMessage>(static_cast<std::size_t>(lookingHoleIndex), new_score, position);
		moleUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitSuccessMessage>(static_cast<std::size_t>(lookingHoleIndex), new_score, position);
	}
	else
	{
		hitterUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitFailMessage>(position);
		moleUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitFailMessage>(position);
	}
	return ret;
}

/// <summary>
/// Looks from specified hole
/// </summary>
/// <param name="holeIndex">Hole index</param>
/// <returns>"true" if looking was successful, otherwise "false"</returns>
bool WhackAStoodentServer::Game::Look(std::size_t holeIndex)
{
	if (holeIndex >= Holes.size())
	{
		throw std::invalid_argument("Hole index is out of bounds.");
	}
	bool ret(lookingHoleIndex < 0);
	if (ret)
	{
		lookingHoleIndex = static_cast<int>(holeIndex);
		hitterUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LookMessage>(holeIndex);
		moleUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LookMessage>(holeIndex);
	}
	return ret;
}

/// <summary>
/// Hides from hole
/// </summary>
/// <returns>"true" if hiding was successful, otherwise "false"</returns>
bool WhackAStoodentServer::Game::Hide()
{
	bool ret(lookingHoleIndex >= 0);
	if (ret)
	{
		lookingHoleIndex = -1;
		hitterUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HideMessage>();
		moleUser.first->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HideMessage>();
	}
	return ret;
}

/// <summary>
/// Processes tick
/// </summary>
void WhackAStoodentServer::Game::ProcessTick(double deltaTime)
{
	if (isGameRunning)
	{
		// TODO: Perform game logic
	}
}
