#pragma once

#include <string>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/ELogLevel.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class LogMessage : public ASerializableMessage<EMessageType::Log>
		{
		public:

			LogMessage();

			LogMessage(ELogLevel logLevel, const std::wstring& logMessage);

			virtual ~LogMessage() override;

			virtual ELogLevel GetLogLevel() const;

			virtual const std::wstring& GetLogMessage() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			ELogLevel logLevel;

			std::wstring logMessage;
		};
	}
}
