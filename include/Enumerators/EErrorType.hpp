#pragma once

namespace WhackAStoodentServer
{
	enum class EErrorType
	{
		Unknown,

		Internal,

		UnsupportedMessageType,

		MalformedMessage,

		InvalidMessageContext
	};
}
