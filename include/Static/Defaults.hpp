#pragma once

#include <cstdint>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes defaults used in Whack-A-Stoodent server
	/// </summary>
	class Defaults
	{
	public:

		/// <summary>
		/// Default server port
		/// </summary>
		static constexpr const std::uint16_t ServerPort = static_cast<const std::uint16_t>(57007);

		/// <summary>
		/// Default timeout time
		/// </summary>
		static constexpr const std::uint32_t TimeoutTime = static_cast<const std::uint32_t>(3000);

		/// <summary>
		/// Default tick count per second
		/// </summary>
		static constexpr const std::uint32_t TickCountPerSecond = static_cast<const std::uint32_t>(120);

		/// <summary>
		/// Default bans file path
		/// </summary>
		static constexpr const char* BansFilePath = "./bans.txt";

		Defaults() = delete;
		Defaults(const Defaults&) = delete;
		Defaults(Defaults&&) = delete;
		~Defaults() = delete;

		Defaults& operator=(const Defaults&) = delete;
		Defaults& operator=(Defaults&&) = delete;
	};
}
