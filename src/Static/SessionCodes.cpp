#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>

/// <summary>
/// Creates new session code
/// </summary>
/// <param name="result">Result</param>
/// <returns>New session code</returns>
std::string& WhackAStoodentServer::SessionCodes::CreateSessionCode(std::string& result)
{
	if (result.length() != WhackAStoodentServer::Rules::SessionCodeCharacterCount)
	{
		result.resize(WhackAStoodentServer::Rules::SessionCodeCharacterCount);
	}
	for (std::size_t index(static_cast<std::size_t>(0)); index != WhackAStoodentServer::Rules::SessionCodeCharacterCount; index++)
	{
		result[index] = sessionCodeCharacters[random() % sessionCodeCharacters.length()];
	}
	return result;
}

/// <summary>
/// IS session code valid
/// </summary>
/// <param name="sessionCode">Session code</param>
/// <returns>"true" if session code is valid, otherwise "false"</returns>
bool WhackAStoodentServer::SessionCodes::IsSessionCodeValid(std::string_view sessionCode)
{
	bool ret(sessionCode.length() == Rules::SessionCodeCharacterCount);
	if (ret)
	{
		for (const char& character : sessionCode)
		{
			if (!std::isalnum(character))
			{
				ret = false;
				break;
			}
		}
	}
	return ret;
}

/// <summary>
/// Session code character
/// </summary>
const std::string WhackAStoodentServer::SessionCodes::sessionCodeCharacters("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

/// <summary>
/// Random number generator
/// </summary>
std::mt19937 WhackAStoodentServer::SessionCodes::random;
