#pragma once

namespace WhackAStoodentServer
{
	enum class EMessageType
	{
		Error,

		Authenticate,

		AcknowledgeAuthentification,

		DenyAuthentification,

		Ping,

		Pong,

		GetMatchHistory,

		MatchHistory,

		PlayWithRandom,

		PlayWithSessionCode,

		RequestPlay,

		AcceptPlayRequest,

		DenyPlayRequest,

		LoadedGame,

		EndGame,

		Hit,

		Look,

		Hide,

		HitSuccess,

		HitFail,

		ScoreMole,

		Log = 0xFF,

		Invalid = -1
	};
}
