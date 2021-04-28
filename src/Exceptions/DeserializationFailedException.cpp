#include <Exceptions/DeserializationFailedException.hpp>

WhackAStoodentServer::DeserializationFailedException::DeserializationFailedException() :
	std::runtime_error("Failed to deserialize object.")
{
	// ...
}

WhackAStoodentServer::DeserializationFailedException::~DeserializationFailedException()
{
	// ...
}
