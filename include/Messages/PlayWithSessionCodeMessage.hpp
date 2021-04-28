#pragma once

#include <uuid.h>
#include <string>

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class PlayWithSessionCodeMessage : public ASerializableMessage<EMessageType::PlayWithSessionCode>
		{
		public:

			static constexpr std::size_t SessionCodeCharacterCount = static_cast<std::size_t>(6);

			PlayWithSessionCodeMessage();

			PlayWithSessionCodeMessage(const std::string& sessionCode);

			virtual ~PlayWithSessionCodeMessage() override;

			virtual const std::string& GetSessionCode() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			std::string sessionCode;
		};
	}
}
