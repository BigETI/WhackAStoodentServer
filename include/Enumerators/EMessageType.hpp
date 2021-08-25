#pragma once

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Message type enumerator
	/// </summary>
	enum class EMessageType
	{
		/// <summary>
		/// Error message type
		/// </summary>
		Error,

		/// <summary>
		/// Authenticate message type
		/// </summary>
		Authenticate,

		/// <summary>
		/// Acknowledge authentification message type
		/// </summary>
		AcknowledgeAuthentification,

		/// <summary>
		/// Deny authentification message type
		/// </summary>
		DenyAuthentification,

		/// <summary>
		/// Ping message type
		/// </summary>
		Ping,

		/// <summary>
		/// Pong message type
		/// </summary>
		Pong,

		/// <summary>
		/// Get match history message type
		/// </summary>
		GetMatchHistory,

		/// <summary>
		/// Match history message type
		/// </summary>
		MatchHistory,

		/// <summary>
		/// Play with a random user message type
		/// </summary>
		PlayWithRandom,

		/// <summary>
		/// Play with specified session code message type
		/// </summary>
		PlayWithSessionCode,

		/// <summary>
		/// Request play message type
		/// </summary>
		RequestPlay,

		/// <summary>
		/// Accept play request 
		/// </summary>
		AcceptPlayRequest,

		/// <summary>
		/// Deny play request messaage type
		/// </summary>
		DenyPlayRequest,

		/// <summary>
		/// User has loaded game message type
		/// </summary>
		LoadedGame,

		/// <summary>
		/// End game message type
		/// </summary>
		EndGame,

		/// <summary>
		/// Hit message type
		/// </summary>
		Hit,

		/// <summary>
		/// Look message type
		/// </summary>
		Look,

		/// <summary>
		/// Hide message type
		/// </summary>
		Hide,

		/// <summary>
		/// Hit was successful message type
		/// </summary>
		HitSuccess,

		/// <summary>
		/// Hit has failed message type
		/// </summary>
		HitFail,

		/// <summary>
		/// Score mole message type
		/// </summary>
		ScoreMole,

		/// <summary>
		/// Log message type
		/// </summary>
		Log = 0xFF,

		/// <summary>
		/// Invalid message type
		/// </summary>
		Invalid = -1
	};
}
