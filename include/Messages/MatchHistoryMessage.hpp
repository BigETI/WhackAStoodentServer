#pragma once

#include <vector>

#include <Abstract/ASerializableMessage.hpp>
#include <Misc/MatchHistoryEntry.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		class MatchHistoryMessage : public ASerializableMessage<EMessageType::MatchHistory>
		{
		public:

			MatchHistoryMessage();

			MatchHistoryMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory);

			MatchHistoryMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory);

			virtual ~MatchHistoryMessage() override;

			virtual const std::vector<WhackAStoodentServer::MatchHistoryEntry>& GetMatchHistory() const;

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		private:

			std::vector<WhackAStoodentServer::MatchHistoryEntry> matchHistory;
		};
	}
}
