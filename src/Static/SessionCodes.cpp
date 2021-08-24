#include <Static/Rules.hpp>
#include <Static/SessionCodes.hpp>

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

bool WhackAStoodentServer::SessionCodes::IsSessionCodeValid(const std::string& sessionCode)
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

const std::string WhackAStoodentServer::SessionCodes::sessionCodeCharacters("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

std::mt19937 WhackAStoodentServer::SessionCodes::random;
