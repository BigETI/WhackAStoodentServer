#pragma once

#include <random>
#include <string>
#include <string_view>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes session codes
	/// </summary>
	class SessionCodes
	{
	public:
		SessionCodes() = delete;
		SessionCodes(const SessionCodes&) = delete;
		SessionCodes(SessionCodes&&) = delete;
		~SessionCodes() = delete;

		/// <summary>
		/// Creates new session code
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>New session code</returns>
		static std::string& CreateSessionCode(std::string& result);

		/// <summary>
		/// IS session code valid
		/// </summary>
		/// <param name="sessionCode">Session code</param>
		/// <returns>"true" if session code is valid, otherwise "false"</returns>
		static bool IsSessionCodeValid(std::string_view sessionCode);

		SessionCodes& operator=(const SessionCodes&) = delete;
		SessionCodes& operator=(SessionCodes&&) = delete;

	private:

		/// <summary>
		/// Session code character
		/// </summary>
		static const std::string sessionCodeCharacters;

		/// <summary>
		/// Random number generator
		/// </summary>
		static std::mt19937 random;
	};
}
