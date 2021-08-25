#pragma once

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Deny play request reason enumerator
	/// </summary>
	enum class EDenyPlayRequestReason
	{
		/// <summary>
		/// No reason
		/// </summary>
		NoReason,

		/// <summary>
		/// User is not interested
		/// </summary>
		NotInterested,

		/// <summary>
		/// User has been blocked
		/// </summary>
		Blocked,

		/// <summary>
		/// An error has occured
		/// </summary>
		Error
	};
}
