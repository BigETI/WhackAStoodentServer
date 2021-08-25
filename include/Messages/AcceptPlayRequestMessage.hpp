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
		/// A class that describes an accept play request message
		/// </summary>
		class AcceptPlayRequestMessage : public ASerializableMessage<EMessageType::AcceptPlayRequest>
		{
		public:

			/// <summary>
			/// Constructs an accept play request message
			/// </summary>
			AcceptPlayRequestMessage();

			/// <summary>
			/// Destroys accept play request message
			/// </summary>
			virtual ~AcceptPlayRequestMessage() override;
		};
	}
}
