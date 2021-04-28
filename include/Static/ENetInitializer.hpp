#pragma once

#include <cstddef>

namespace WhackAStoodentServer
{
	class ENetInitializer
	{
	public:

		ENetInitializer() = delete;
		ENetInitializer(const ENetInitializer&) = delete;
		ENetInitializer(ENetInitializer&&) = delete;
		~ENetInitializer() = delete;

		static void Initialize();

		static bool Deinitialize();

		static std::size_t GetInitializationCount();

		ENetInitializer& operator=(const ENetInitializer&) = delete;
		ENetInitializer& operator=(ENetInitializer&&) = delete;

	private:

		static std::size_t initializationCount;
	};
}
