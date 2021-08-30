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
		/// A class that describes an end game message
		/// </summary>
		class EndGameMessage : public ASerializableMessage<EMessageType::EndGame>
		{
		public:

			/// <summary>
			/// Constructs an end game message
			/// </summary>
			EndGameMessage();

			/// <summary>
			/// Constructs an end game message
			/// </summary>
			/// <param name="matchHistory">Match history</param>
			EndGameMessage(const std::vector<WhackAStoodentServer::MatchHistoryEntry>& matchHistory);

			/// <summary>
			/// Constructs an end game message
			/// </summary>
			/// <param name="matchHistory">Match history</param>
			EndGameMessage(std::vector<WhackAStoodentServer::MatchHistoryEntry>&& matchHistory);

			/// <summary>
			/// Destroys end game message
			/// </summary>
			virtual ~EndGameMessage() override;

			/// <summary>
			/// Gets the current match history
			/// </summary>
			/// <returns>Match history</returns>
			virtual const std::vector<WhackAStoodentServer::MatchHistoryEntry>& GetMatchHistory() const;

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
			virtual std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Match history
			/// </summary>
			std::vector<WhackAStoodentServer::MatchHistoryEntry> matchHistory;
		};
	}
}
