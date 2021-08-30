#pragma once

#include <cstdint>
#include <random>
#include <span>
#include <string>
#include <string_view>
#include <vector>

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
		static constexpr const char* EmptySessionCode = "000000";

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

		/// <summary>
		/// Serializes session code
		/// </summary>
		/// <param name="sessionCode">Session code</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized session code</returns>
		static std::vector<std::uint8_t>& Serialize(std::string_view sessionCode, std::vector<std::uint8_t>& result);

		/// <summary>
		/// Deserializes session code
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> bytes, std::string& result);

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
