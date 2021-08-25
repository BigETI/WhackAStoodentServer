#pragma once

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Disconnection reason enumerator
	/// </summary>
	enum class EDisconnectionReason
	{
		/// <summary>
		/// No reason
		/// </summary>
		NoReason,

		/// <summary>
		/// Kicked
		/// </summary>
		Kicked,

		/// <summary>
		/// Banned
		/// </summary>
		Banned,

		/// <summary>
		/// Stopped
		/// </summary>
		Stopped
	};
}
