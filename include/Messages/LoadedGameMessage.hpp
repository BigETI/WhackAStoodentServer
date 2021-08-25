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
		/// A class that describes a loaded game message
		/// </summary>
		class LoadedGameMessage : public ASerializableMessage<EMessageType::LoadedGame>
		{
		public:

			/// <summary>
			/// Constructs a loaded game message
			/// </summary>
			LoadedGameMessage();

			/// <summary>
			/// Destroys loaded game message
			/// </summary>
			virtual ~LoadedGameMessage() override;
		};
	}
}
