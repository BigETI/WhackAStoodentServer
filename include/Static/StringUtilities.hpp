#pragma once

#include <string>
#include <string_view>
#include <vector>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that provides string utilities
	/// </summary>
	class StringUtilities
	{
	public:
		StringUtilities() = delete;
		StringUtilities(const StringUtilities&) = delete;
		StringUtilities(StringUtilities&&) = delete;
		~StringUtilities() = delete;

		/// <summary>
		/// Trims the specified string
		/// </summary>
		/// <param name="string">String</param>
		/// <returns>Trimmed string</returns>
		static std::string_view TrimString(std::string_view string);

		/// <summary>
		/// Splits string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="delimiter">Delimiter</param>
		/// <param name="result">Result</param>
		/// <returns>Splitted string</returns>
		static std::vector<std::string>& SplitString(std::string_view string, std::string_view delimiter, std::vector<std::string>& result);

		StringUtilities& operator=(const StringUtilities&) = delete;
		StringUtilities& operator=(StringUtilities&&) = delete;
	};
}
