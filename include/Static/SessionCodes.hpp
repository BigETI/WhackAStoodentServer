#pragma once

#include <random>
#include <string>

namespace WhackAStoodentServer
{
	class SessionCodes
	{
	public:
		SessionCodes() = delete;
		SessionCodes(const SessionCodes&) = delete;
		SessionCodes(SessionCodes&&) = delete;
		~SessionCodes() = delete;

		static std::string& CreateSessionCode(std::string& result);

		static bool IsSessionCodeValid(const std::string& sessionCode);

		SessionCodes& operator=(const SessionCodes&) = delete;
		SessionCodes& operator=(SessionCodes&&) = delete;

	private:

		static const std::string sessionCodeCharacters;

		static std::mt19937 random;
	};
}
