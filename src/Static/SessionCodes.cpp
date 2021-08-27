#include <cstring>

#include <Static/NumericSerializer.hpp>
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
/// Serializes session code
/// </summary>
/// <param name="sessionCode">Session code</param>
/// <param name="result">Result</param>
/// <returns>Serialized session code</returns>
std::vector<std::uint8_t>& WhackAStoodentServer::SessionCodes::Serialize(std::string_view sessionCode, std::vector<std::uint8_t>& result)
{
	std::string_view session_code(SessionCodes::IsSessionCodeValid(sessionCode) ? sessionCode : WhackAStoodentServer::SessionCodes::EmptySessionCode);
	std::size_t offset(result.size());
	result.resize(result.size() + (WhackAStoodentServer::Rules::SessionCodeCharacterCount * sizeof(std::string::value_type)));
	std::memcpy(result.data() + offset, session_code.data(), WhackAStoodentServer::Rules::SessionCodeCharacterCount * sizeof(std::string::value_type));
	return result;
}

/// <summary>
/// Deserializes session code
/// </summary>
/// <param name="bytes">Data</param>
/// <param name="result">Result</param>
/// <returns>Remaining data to be deserialized</returns>
std::span<const std::uint8_t> WhackAStoodentServer::SessionCodes::Deserialize(const std::span<const std::uint8_t> bytes, std::string& result)
{
	if (bytes.size() < WhackAStoodentServer::Rules::SessionCodeCharacterCount)
	{
		throw WhackAStoodentServer::DeserializationFailedException();
	}
	if (result.length() != WhackAStoodentServer::Rules::SessionCodeCharacterCount)
	{
		result.resize(WhackAStoodentServer::Rules::SessionCodeCharacterCount);
	}
	std::memcpy(result.data(), bytes.data(), WhackAStoodentServer::Rules::SessionCodeCharacterCount * sizeof(std::string::value_type));
	return bytes.subspan<WhackAStoodentServer::Rules::SessionCodeCharacterCount * sizeof(std::string::value_type)>();
}

/// <summary>
/// Session code character
/// </summary>
const std::string WhackAStoodentServer::SessionCodes::sessionCodeCharacters("123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

/// <summary>
/// Random number generator
/// </summary>
std::mt19937 WhackAStoodentServer::SessionCodes::random;
