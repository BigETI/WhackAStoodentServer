#pragma once

#include <vector>

#include <Abstract/ASerializableMessage.hpp>
#include <Misc/MatchHistoryEntry.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Whack-A-Stoodent server messages namespace
	/// </summary>
	namespace Messages
	{
		/// <summary>
		/// A class that describes a match history message
		/// </summary>
		class MatchHistoryMessage : public ASerializableMessage<EMessageType::MatchHistory>
		{
		public:

			/// <summary>
			/// Constructs a match history message
			/// </summary>
			MatchHistoryMessage();

			/// <summary>
			/// Constructs a match history message
			/// </summary>
			/// <param name="matchHistory">Match history</param>
			MatchHistoryMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory);

			/// <summary>
			/// Constructs a match history message
			/// </summary>
			/// <param name="matchHistory">Match history</param>
			MatchHistoryMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory);

			/// <summary>
			/// Destroys match history message
			/// </summary>
			virtual ~MatchHistoryMessage() override;

			/// <summary>
			/// Gets match history
			/// </summary>
			/// <returns>Match history</returns>
			virtual nonstd::span<const WhackAStoodentServer::MatchHistoryEntry> GetMatchHistory() const;

			/// <summary>
			/// Serializes contents
			/// </summary>
			/// <param name="result">Result</param>
			/// <returns>Serialized contents</returns>
			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			/// <summary>
			/// Deserializes given input
			/// </summary>
			/// <param name="data">Data to deserialize</param>
			/// <returns>Remaining data to deserialize</returns>
			virtual nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Match history
			/// </summary>
			std::vector<WhackAStoodentServer::MatchHistoryEntry> matchHistory;
		};
	}
}
