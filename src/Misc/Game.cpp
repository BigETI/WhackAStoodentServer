#include <Messages/HideMessage.hpp>
#include <Messages/HitFailMessage.hpp>
#include <Messages/HitSuccessMessage.hpp>
#include <Messages/LoadedGameMessage.hpp>
#include <Messages/LookMessage.hpp>
#include <Messages/ScoreMoleMessage.hpp>
#include <Misc/Game.hpp>
#include <Static/Rules.hpp>

/// <summary>
/// Holes
/// </summary>
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
/// <param name="gameID">Game ID</param>
/// <param name="hitterUser">User (hitter)</param>
/// <param name="moleUser">User (mole)</param>
WhackAStoodentServer::Game::Game(const uuids::uuid& gameID, std::shared_ptr<WhackAStoodentServer::User> hitterUser, std::shared_ptr<WhackAStoodentServer::User> moleUser) :
	gameID(gameID),
	hitterUser(hitterUser),
	moleUser(moleUser),
	isGameRunning(false),
	gameStartedTimePoint(std::chrono::high_resolution_clock::now()),
	lookingHoleIndex(-1)
{
	if (gameID.is_nil())
	{
		throw std::invalid_argument("Parameter \"gameID\" is nil.");
	}
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
/// Gets the game ID
/// </summary>
/// <returns>Game ID</returns>
const uuids::uuid& WhackAStoodentServer::Game::GetGameID() const
{
	return gameID;
}

/// <summary>
/// Is game loaded
/// </summary>
/// <param name="role">Role</param>
/// <returns>"true" if game is loaded, otherwise "false"</returns>
bool WhackAStoodentServer::Game::IsGameLoaded(WhackAStoodentServer::EPlayerRole role) const
{
	return (role == WhackAStoodentServer::EPlayerRole::Hitter) ? hitterUser->IsGameLoaded() : moleUser->IsGameLoaded();
}

/// <summary>
/// Is game loaded for user
/// </summary>
/// <param name="user">User</param>
/// <returns>"true" if game is loaded, otherwise "false"</returns>
bool WhackAStoodentServer::Game::IsGameLoadedForUser(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	return IsGameLoaded(GetPlayerRole(user));
}

/// <summary>
/// Are games loaded
/// </summary>
/// <returns>"true" if games are loaded, otherwise "false"</returns>
bool WhackAStoodentServer::Game::AreGamesLoaded() const
{
	return hitterUser->IsGameLoaded() && moleUser->IsGameLoaded();
}

/// <summary>
/// Is game running
/// </summary>
/// <returns>"true" if game is running, otherwise "false"</returns>
bool WhackAStoodentServer::Game::IsGameRunning() const
{
	return isGameRunning;
}

/// <summary>
/// Is game finished
/// </summary>
/// <returns>"true" if game is finished, otherwise "false"</returns>
bool WhackAStoodentServer::Game::IsGameFinished() const
{
	return isGameFinished;
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
		hitterUser->SetScore(0L);
		moleUser->SetScore(0L);
		hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LoadedGameMessage>();
		moleUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LoadedGameMessage>();
		OnGameStarted();
	}
	return ret;
}

/// <summary>
/// Finishes game
/// </summary>
/// <returns>"true" if game has been successfully stopped, otherwise "false"</returns>
bool WhackAStoodentServer::Game::FinishGame()
{
	bool ret(isGameRunning);
	if (ret)
	{
		isGameRunning = false;
		isGameFinished = true;
		hitterUser->SetGameLoadedState(false);
		moleUser->SetGameLoadedState(false);
		OnGameFinished();
	}
	return ret;
}

/// <summary>
/// Gets the player role
/// </summary>
/// <returns>Player role</returns>
WhackAStoodentServer::EPlayerRole WhackAStoodentServer::Game::GetPlayerRole(std::shared_ptr<WhackAStoodentServer::User> user) const
{
	if (!user)
	{
		throw std::invalid_argument("Parameter \"user\" is null.");
	}
	WhackAStoodentServer::EPlayerRole ret;
	if (user == hitterUser)
	{
		ret = WhackAStoodentServer::EPlayerRole::Hitter;
	}
	else if (user == moleUser)
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
	bool ret((std::chrono::high_resolution_clock::now() - lastHitTimePoint) >= WhackAStoodentServer::Rules::HittingCooldownTime);
	if (ret)
	{
		ret = (lookingHoleIndex >= 0) && Holes[lookingHoleIndex].IsPositionInHole(position);
		if (ret)
		{
			std::int64_t new_score(hitterUser->GetScore() + WhackAStoodentServer::Rules::HittingScore);
			lookingHoleIndex = -1;
			hitterUser->SetScore(new_score);
			hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitSuccessMessage>(static_cast<std::size_t>(lookingHoleIndex), new_score, position);
			moleUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitSuccessMessage>(static_cast<std::size_t>(lookingHoleIndex), new_score, position);
		}
		else
		{
			hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitFailMessage>(position);
			moleUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HitFailMessage>(position);
		}
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
	bool ret(lookingHoleIndex != holeIndex);
	if (ret)
	{
		lookingHoleIndex = static_cast<int>(holeIndex);
		lastLookingTickTimePoint = std::chrono::high_resolution_clock::now();
		hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LookMessage>(holeIndex);
		moleUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::LookMessage>(holeIndex);
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
		hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HideMessage>();
		moleUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::HideMessage>();
	}
	return ret;
}

/// <summary>
/// Processes tick
/// </summary>
void WhackAStoodentServer::Game::ProcessTick()
{
	if (isGameRunning)
	{
		if ((std::chrono::high_resolution_clock::now() - gameStartedTimePoint) < WhackAStoodentServer::Rules::PlayTime)
		{
			if (lookingHoleIndex >= 0)
			{
				std::chrono::nanoseconds elapsed_look_tick_time(std::chrono::high_resolution_clock::now() - lastLookingTickTimePoint);
				bool is_sending_mole_scored_message(false);
				while (elapsed_look_tick_time >= WhackAStoodentServer::Rules::LookingTickTime)
				{
					lastLookingTickTimePoint += WhackAStoodentServer::Rules::LookingTickTime;
					elapsed_look_tick_time -= WhackAStoodentServer::Rules::LookingTickTime;
					moleUser->SetScore(moleUser->GetScore() + WhackAStoodentServer::Rules::LookingScorePerLookingTick);
					is_sending_mole_scored_message = true;
				}
				if (is_sending_mole_scored_message)
				{
					hitterUser->GetPeer().SendPeerMessage<WhackAStoodentServer::Messages::ScoreMoleMessage>(moleUser->GetScore());
				}
			}
		}
		else
		{
			FinishGame();
		}
	}
}
