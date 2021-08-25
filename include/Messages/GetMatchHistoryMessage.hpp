#pragma once

#include <Abstract/ASerializableMessage.hpp>

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
		/// A class that describes a get match history message
		/// </summary>
		class GetMatchHistoryMessage : public ASerializableMessage<EMessageType::GetMatchHistory>
		{
		public:

			/// <summary>
			/// Construicts a get match history message
			/// </summary>
			GetMatchHistoryMessage();

			/// <summary>
			/// Destroys get match history message
			/// </summary>
			virtual ~GetMatchHistoryMessage() override;
		};
	}
}
