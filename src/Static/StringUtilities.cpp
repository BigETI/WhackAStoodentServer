#include <array>
#include <string>

#include <Static/StringUtilities.hpp>

/// <summary>
/// Trims the specified string
/// </summary>
/// <param name="string">String</param>
/// <returns>Trimmed string</returns>
std::string_view WhackAStoodentServer::StringUtilities::TrimString(std::string_view input)
{
	std::size_t left_offset(static_cast<std::size_t>(0));
	std::size_t right_offset(static_cast<std::size_t>(0));
	for (std::size_t position(static_cast<std::size_t>(0)); position != input.length(); position++)
	{
		left_offset = position;
		if (!std::isspace(input[position]))
		{
			break;
		}
	}
	for (std::size_t position(static_cast<std::size_t>(0)); position != input.length(); position++)
	{
		right_offset = position;
		if (!std::isspace(input[input.length() - position]))
		{
			break;
		}
	}
	return input.substr(left_offset, input.length() - left_offset - right_offset);
}

/// <summary>
/// Splits string
/// </summary>
/// <param name="string">String</param>
/// <param name="delimiter">Delimiter</param>
/// <param name="result">Result</param>
/// <returns>Splitted string</returns>
std::vector<std::string>& WhackAStoodentServer::StringUtilities::SplitString(std::string_view input, std::string_view delimiter, std::vector<std::string>& result)
{
	std::size_t begin_position(static_cast<std::size_t>(0));
	std::size_t position(static_cast<std::size_t>(0));
	result.clear();
	while ((position = input.find(delimiter, begin_position)) != std::string_view::npos)
	{
		result.push_back(std::string(input.substr(begin_position, begin_position - position)));
		begin_position = position + delimiter.length();
	}
	if (begin_position < input.length())
	{
		result.push_back(std::string(input.substr(begin_position)));
	}
	return result;
}
