#pragma once

#include <cstddef>

namespace WhackAStoodentServer
{
	class Rules
	{
	public:

		static constexpr std::size_t MaximalNameLength = static_cast<std::size_t>(24);

		static constexpr std::size_t SessionCodeCharacterCount = static_cast<std::size_t>(6);

		Rules() = delete;
		Rules(const Rules&) = delete;
		Rules(Rules&&) = delete;
		~Rules() = delete;

		Rules& operator=(const Rules&) = delete;
		Rules& operator=(Rules&&) = delete;
	};
}
