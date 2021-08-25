#pragma once

#include <cstddef>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an ENet initializer
	/// </summary>
	class ENetInitializer
	{
	public:

		ENetInitializer() = delete;
		ENetInitializer(const ENetInitializer&) = delete;
		ENetInitializer(ENetInitializer&&) = delete;
		~ENetInitializer() = delete;

		/// <summary>
		/// Initializes ENet
		/// </summary>
		static void Initialize();

		/// <summary>
		/// Deinitializes ENet
		/// </summary>
		/// <returns>"true" if ENet has been successfull deinitialized, otherwise "false"</returns>
		static bool Deinitialize();

		/// <summary>
		/// Get the initialization count
		/// </summary>
		/// <returns>Initialization count</returns>
		static std::size_t GetInitializationCount();

		ENetInitializer& operator=(const ENetInitializer&) = delete;
		ENetInitializer& operator=(ENetInitializer&&) = delete;

	private:

		/// <summary>
		/// Initialization count
		/// </summary>
		static std::size_t initializationCount;
	};
}
