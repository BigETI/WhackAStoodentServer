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
		/// A class that describes a hide message
		/// </summary>
		class HideMessage : public ASerializableMessage<EMessageType::Hide>
		{
		public:

			/// <summary>
			/// Constructs a hide message
			/// </summary>
			HideMessage();

			/// <summary>
			/// Destroys hide message
			/// </summary>
			virtual ~HideMessage() override;
		};
	}
}
