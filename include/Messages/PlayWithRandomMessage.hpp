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
		/// A class that describes a play with random message
		/// </summary>
		class PlayWithRandomMessage : public ASerializableMessage<EMessageType::PlayWithRandom>
		{
		public:

			/// <summary>
			/// Constructs a play with random message
			/// </summary>
			PlayWithRandomMessage();

			/// <summary>
			/// Destroys play with random message
			/// </summary>
			virtual ~PlayWithRandomMessage() override;
		};
	}
}
