#include <Misc/Game.hpp>

WhackAStoodentServer::Game::Game(const std::array<std::shared_ptr<WhackAStoodentServer::User>, static_cast<std::size_t>(2)>& users) : users(users)
{
	// ...
}

WhackAStoodentServer::Game::~Game()
{
	// ...
}
