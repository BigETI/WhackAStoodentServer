#pragma once

#include <cstdint>
#include <string>

#include <Interfaces/ISerializable.hpp>

namespace WhackAStoodentServer
{
	class MatchHistoryEntry : ISerializable
	{
	public:

		MatchHistoryEntry();

		MatchHistoryEntry(const MatchHistoryEntry& matchHistoryEntry);

		MatchHistoryEntry(MatchHistoryEntry&& matchHistoryEntry);

		MatchHistoryEntry(std::int64_t yourScore, std::wstring yourName, std::int64_t opponentScore, std::wstring opponentName);

		virtual ~MatchHistoryEntry();

		virtual std::int64_t GetYourScore() const;

		virtual const std::wstring& GetYourName() const;

		virtual std::int64_t GetOpponentScore() const;

		virtual const std::wstring& GetOpponentName() const;

		virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

		virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override;

		virtual MatchHistoryEntry& operator=(const MatchHistoryEntry& matchHistoryEntry);

		virtual MatchHistoryEntry& operator=(MatchHistoryEntry&& matchHistoryEntry) noexcept;

	private:

		std::int64_t yourScore;

		std::wstring yourName;

		std::int64_t opponentScore;

		std::wstring opponentName;
	};
}
