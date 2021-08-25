#include <Exceptions/DeserializationFailedException.hpp>

/// <summary>
/// Constructs a deserialization exception
/// </summary>
WhackAStoodentServer::DeserializationFailedException::DeserializationFailedException() :
	std::runtime_error("Failed to deserialize object.")
{
	// ...
}

/// <summary>
/// Destroys deserialization exception
/// </summary>
WhackAStoodentServer::DeserializationFailedException::~DeserializationFailedException()
{
	// ...
}
