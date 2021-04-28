#pragma once

#include <string>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EErrorType.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class ErrorMessage : public ASerializableMessage<EMessageType::Error>
		{
		public:

			ErrorMessage();

			ErrorMessage(EErrorType errorType, const std::wstring& errorMessage);

			virtual ~ErrorMessage() override;

			virtual EErrorType GetErrorType() const;

			virtual const std::wstring& GetErrorMessage() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			EErrorType errorType;

			std::wstring errorMessage;
		};
	}
}
