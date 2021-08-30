#pragma once

#include <chrono>
#include <memory>
#include <utility>

#include <uuid.h>

#include <Enumerators/EPlayerRole.hpp>
#include <Misc/Event.hpp>
#include <Misc/Hole.hpp>
#include <Misc/User.hpp>
#include <Misc/Vector2D.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a game
	/// </summary>
	class Game
	{
	public:

		/// <summary>
		/// Holes
		/// </summary>
		static const std::array<const Hole, 4ULL> Holes;

		/// <summary>
		/// Used to invoke when game has been started
		/// </summary>
		Event<> OnGameStarted;

		/// <summary>
		/// Used to invoke when game has been finished
		/// </summary>
		Event<> OnGameFinished;

		Game() = delete;

		/// <summary>
		/// Constructs a game
		/// </summary>
		/// <param name="gameID">Game ID</param>
		/// <param name="hitterUser">User (hitter)</param>
		/// <param name="moleUser">User (mole)</param>
		Game(const uuids::uuid& gameID, std::shared_ptr<User> hitterUser, std::shared_ptr<User> moleUser);

		/// <summary>
		/// Destroys game
		/// </summary>
		virtual ~Game();

		/// <summary>
		/// Gets the game ID
		/// </summary>
		/// <returns>Game ID</returns>
		virtual const uuids::uuid& GetGameID() const;

		/// <summary>
		/// Is game loaded
		/// </summary>
		/// <param name="role">Role</param>
		/// <returns>"true" if game is loaded, otherwise "false"</returns>
		virtual bool IsGameLoaded(EPlayerRole role) const;

		/// <summary>
		/// Is game loaded for user
		/// </summary>
		/// <param name="user">User</param>
		/// <returns>"true" if game is loaded, otherwise "false"</returns>
		virtual bool IsGameLoadedForUser(std::shared_ptr<User> user) const;

		/// <summary>
		/// Are games loaded
		/// </summary>
		/// <returns>"true" if games are loaded, otherwise "false"</returns>
		virtual bool AreGamesLoaded() const;

		/// <summary>
		/// Is game running
		/// </summary>
		/// <returns>"true" if game is running, otherwise "false"</returns>
		virtual bool IsGameRunning() const;

		/// <summary>
		/// Is game finished
		/// </summary>
		/// <returns>"true" if game is finished, otherwise "false"</returns>
		virtual bool IsGameFinished() const;

		/// <summary>
		/// Starts game
		/// </summary>
		/// <returns>"true" if game has been successfully started, otherwise "false"</returns>
		virtual bool StartGame();

		/// <summary>
		/// Finishes game
		/// </summary>
		/// <returns>"true" if game has been successfully stopped, otherwise "false"</returns>
		virtual bool FinishGame();

		/// <summary>
		/// Gets the player role
		/// </summary>
		/// <returns>Player role</returns>
		virtual EPlayerRole GetPlayerRole(std::shared_ptr<User> user) const;

		/// <summary>
		/// Hits at the given position
		/// </summary>
		/// <param name="position">Position</param>
		/// <returns>"true" if hitting was successful, otherwise "false"</returns>
		virtual bool Hit(const Vector2D<float>& position);

		/// <summary>
		/// Looks from specified hole
		/// </summary>
		/// <param name="holeIndex">Hole index</param>
		/// <returns>"true" if looking was successful, otherwise "false"</returns>
		virtual bool Look(std::size_t holeIndex);

		/// <summary>
		/// Hides from hole
		/// </summary>
		/// <returns>"true" if hiding was successful, otherwise "false"</returns>
		virtual bool Hide();

		/// <summary>
		/// Processes tick
		/// </summary>
		virtual void ProcessTick();

	private:

		/// <summary>
		/// Game ID
		/// </summary>
		uuids::uuid gameID;

		/// <summary>
		/// Hitter user
		/// </summary>
		std::pair<std::shared_ptr<User>, bool> hitterUser;

		/// <summary>
		/// Mole user
		/// </summary>
		std::pair<std::shared_ptr<User>, bool> moleUser;

		/// <summary>
		/// Is game running
		/// </summary>
		bool isGameRunning;

		/// <summary>
		/// Is game finished
		/// </summary>
		bool isGameFinished;

		/// <summary>
		/// Game started time point
		/// </summary>
		std::chrono::high_resolution_clock::time_point gameStartedTimePoint;

		/// <summary>
		/// Looking hole index
		/// </summary>
		int lookingHoleIndex;

		/// <summary>
		/// Last hit time point
		/// </summary>
		std::chrono::high_resolution_clock::time_point lastHitTimePoint;

		/// <summary>
		/// Last looking tick time point
		/// </summary>
		std::chrono::high_resolution_clock::time_point lastLookingTickTimePoint;
	};
}
