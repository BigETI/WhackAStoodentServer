#pragma once

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Error type enumerator
	/// </summary>
	enum class EErrorType
	{
		/// <summary>
		/// Unknown error
		/// </summary>
		Unknown,

		/// <summary>
		/// Internal error
		/// </summary>
		Internal,

		/// <summary>
		/// Unsupported message type
		/// </summary>
		UnsupportedMessageType,

		/// <summary>
		/// Malformed message
		/// </summary>
		MalformedMessage,

		/// <summary>
		/// Invalid message context
		/// </summary>
		InvalidMessageContext
	};
}
