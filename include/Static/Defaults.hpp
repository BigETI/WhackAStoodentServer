#pragma once

#include <cstdint>

namespace WhackAStoodentServer
{
	class Defaults
	{
	public:

		static constexpr std::uint16_t ServerPort = static_cast<std::uint16_t>(57007);

		static constexpr std::uint32_t TimeoutTime = static_cast<std::uint32_t>(3000);

		static constexpr std::uint32_t TickCountPerSecond = static_cast<std::uint32_t>(120);

		Defaults() = delete;
		Defaults(const Defaults&) = delete;
		Defaults(Defaults&&) = delete;
		~Defaults() = delete;

		Defaults& operator=(const Defaults&) = delete;
		Defaults& operator=(Defaults&&) = delete;
	};
}
