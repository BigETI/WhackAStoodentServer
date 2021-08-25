#include <Misc/Game.hpp>

/// <summary>
/// Constructs a game
/// </summary>
/// <param name="users"></param>
WhackAStoodentServer::Game::Game(const std::array<std::shared_ptr<WhackAStoodentServer::User>, static_cast<std::size_t>(2)>& users) : users(users)
{
	// ...
}

/// <summary>
/// Destroys game
/// </summary>
WhackAStoodentServer::Game::~Game()
{
	// ...
}
