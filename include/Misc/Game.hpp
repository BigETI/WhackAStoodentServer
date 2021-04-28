#pragma once

#include <array>
#include <memory>

#include <Misc/User.hpp>

namespace WhackAStoodentServer
{
	class Game
	{
	public:

		Game() = delete;

		Game(const std::array<std::shared_ptr<User>, static_cast<std::size_t>(2)>& users);

		virtual ~Game();

	private:

		std::array<std::shared_ptr<User>, static_cast<std::size_t>(2)> users;
	};
}
