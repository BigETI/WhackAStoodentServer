#pragma once

#include <string>

#include <uuid.h>

#include <Abstract/ASerializableMessage.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class AuthenticateMessage : public ASerializableMessage<EMessageType::Authenticate>
		{
		public:

			AuthenticateMessage();

			AuthenticateMessage(const uuids::uuid& userID, const std::wstring& username);

			virtual ~AuthenticateMessage() override;

			virtual const uuids::uuid& GetUserID() const;

			virtual const std::wstring& GetUsername() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			uuids::uuid userID;

			std::wstring username;
		};
	}
}
