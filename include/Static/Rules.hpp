#pragma once

#include <cstddef>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a set of rules
	/// </summary>
	class Rules
	{
	public:

		/// <summary>
		/// Maximal name length
		/// </summary>
		static constexpr const std::size_t MaximalNameLength = static_cast<const std::size_t>(24);

		/// <summary>
		/// Session code character count
		/// </summary>
		static constexpr const std::size_t SessionCodeCharacterCount = static_cast<const std::size_t>(6);

		Rules() = delete;
		Rules(const Rules&) = delete;
		Rules(Rules&&) = delete;
		~Rules() = delete;

		Rules& operator=(const Rules&) = delete;
		Rules& operator=(Rules&&) = delete;
	};
}
