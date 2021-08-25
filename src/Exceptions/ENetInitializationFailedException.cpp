#include <Exceptions/ENetInitializationFailedException.hpp>

/// <summary>
/// Constructs an ENet intialization failed exception
/// </summary>
/// <param name="errorCode">Error code</param>
WhackAStoodentServer::ENetInitializationFailedException::ENetInitializationFailedException(int errorCode) :
	std::runtime_error("Failed to initialize ENet. Error code: " + std::to_string(errorCode)),
	errorCode(errorCode)
{
	// ...
}

/// <summary>
/// Destroys ENet intialization failed exception
/// </summary>
WhackAStoodentServer::ENetInitializationFailedException::~ENetInitializationFailedException()
{
	// ...
}

/// <summary>
/// Gets the error code
/// </summary>
/// <returns>Error code</returns>
int WhackAStoodentServer::ENetInitializationFailedException::GetErrorCode() const
{
	return errorCode;
}
