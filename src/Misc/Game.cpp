#include <Misc/Game.hpp>

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
