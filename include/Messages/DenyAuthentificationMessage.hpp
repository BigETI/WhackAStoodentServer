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
		/// A class that describes a deny authentification message
		/// </summary>
		class DenyAuthentificationMessage : public ASerializableMessage<EMessageType::DenyAuthentification>
		{
		public:

			/// <summary>
			/// Constructs a deny authentification message
			/// </summary>
			DenyAuthentificationMessage();

			/// <summary>
			/// Destroys deny authentification message
			/// </summary>
			virtual ~DenyAuthentificationMessage() override;
		};
	}
}
