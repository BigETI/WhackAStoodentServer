#pragma once

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EPlayerRole.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class RequestPlayMessage : public ASerializableMessage<EMessageType::RequestPlay>
		{
		public:

			RequestPlayMessage();

			RequestPlayMessage(EPlayerRole playerRole, const std::wstring& opponentName);

			virtual ~RequestPlayMessage();

			virtual EPlayerRole GetPlayerRole() const;

			virtual const std::wstring& GetOpponentName() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			EPlayerRole playerRole;

			std::wstring opponentName;
		};
	}
}
