#include <Exceptions/ENetInitializationFailedException.hpp>

WhackAStoodentServer::ENetInitializationFailedException::ENetInitializationFailedException(int errorCode) :
	std::runtime_error("Failed to initialize ENet. Error code: " + std::to_string(errorCode)),
	errorCode(errorCode)
{
	// ...
}

WhackAStoodentServer::ENetInitializationFailedException::~ENetInitializationFailedException()
{
	// ...
}

int WhackAStoodentServer::ENetInitializationFailedException::GetErrorCode() const
{
	return errorCode;
}
