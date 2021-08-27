#pragma once

#include <chrono>
#include <memory>
#include <utility>

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

		Event<> OnGameStarted;

		Event<> OnGameStopped;

		Game() = delete;

		/// <summary>
		/// Constructs a game
		/// </summary>
		/// <param name="hitterUser">User (hitter)(</param>
		/// <param name="moleUser">User (mole)(</param>
		Game(std::shared_ptr<User> hitterUser, std::shared_ptr<User> moleUser);

		/// <summary>
		/// Destroys game
		/// </summary>
		virtual ~Game();

		/// <summary>
		/// Is game loaded
		/// </summary>
		/// <param name="role">Role</param>
		virtual bool IsGameLoaded(EPlayerRole role) const;

		/// <summary>
		/// Is game loaded for user
		/// </summary>
		/// <param name="user">User</param>
		virtual bool IsGameLoadedForUser(std::shared_ptr<User> user) const;

		/// <summary>
		/// Are games loaded
		/// </summary>
		virtual bool AreGamesLoaded() const;

		/// <summary>
		/// Is game running
		/// </summary>
		virtual bool IsGameRunning() const;

		/// <summary>
		/// Starts game
		/// </summary>
		/// <returns>"true" if game has been successfully started, otherwise "false"</returns>
		virtual bool StartGame();

		/// <summary>
		/// Stops game
		/// </summary>
		virtual bool StopGame();

		/// <summary>
		/// Gets player role
		/// </summary>
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
		virtual void ProcessTick(double deltaTime);

	private:

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
		/// Game started time point
		/// </summary>
		std::chrono::steady_clock::time_point gameStartedTimePoint;

		/// <summary>
		/// Looking hole index
		/// </summary>
		int lookingHoleIndex;
	};
}
