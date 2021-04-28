#pragma once

#include <stdexcept>
#include <string>

namespace WhackAStoodentServer
{
	class DeserializationFailedException : public std::runtime_error
	{
	public:

		DeserializationFailedException();

		virtual ~DeserializationFailedException();
	};
}
