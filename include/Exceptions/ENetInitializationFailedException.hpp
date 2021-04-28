#pragma once

#include <stdexcept>
#include <string>

namespace WhackAStoodentServer
{
	class ENetInitializationFailedException : public std::runtime_error
	{
	public:

		ENetInitializationFailedException() = delete;

		ENetInitializationFailedException(int errorCode);

		virtual ~ENetInitializationFailedException();

		virtual int GetErrorCode() const;

	private:

		int errorCode;
	};
}
