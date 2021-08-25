#pragma once

#include <array>
#include <memory>

#include <Misc/User.hpp>

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

		Game() = delete;

		/// <summary>
		/// Constructs a game
		/// </summary>
		/// <param name="users"></param>
		Game(const std::array<std::shared_ptr<User>, static_cast<std::size_t>(2)>& users);

		/// <summary>
		/// Destroys game
		/// </summary>
		virtual ~Game();

	private:

		/// <summary>
		/// Users
		/// </summary>
		std::array<std::shared_ptr<User>, static_cast<std::size_t>(2)> users;
	};
}
