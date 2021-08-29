#include <enet.h>

#include <Exceptions/ENetInitializationFailedException.hpp>
#include <Static/ENetInitializer.hpp>

/// <summary>
/// Initialization count
/// </summary>
std::size_t WhackAStoodentServer::ENetInitializer::initializationCount(static_cast<std::size_t>(0));

/// <summary>
/// Initializes ENet
/// </summary>
void WhackAStoodentServer::ENetInitializer::Initialize()
{
	if (initializationCount == static_cast<std::size_t>(0))
	{
		int error_code(enet_initialize());
		if (error_code)
		{
			throw WhackAStoodentServer::ENetInitializationFailedException(error_code);
		}
	}
}

/// <summary>
/// Deinitializes ENet
/// </summary>
/// <returns>"true" if ENet has been successfull deinitialized, otherwise "false"</returns>
bool WhackAStoodentServer::ENetInitializer::Deinitialize()
{
	bool ret(initializationCount > static_cast<std::size_t>(0));
	if (initializationCount == static_cast<std::size_t>(1))
	{
		enet_deinitialize();
	}
	if (ret)
	{
		--initializationCount;
	}
	return ret;
}

/// <summary>
/// Get the initialization count
/// </summary>
/// <returns>Initialization count</returns>
std::size_t WhackAStoodentServer::ENetInitializer::GetInitializationCount()
{
	return initializationCount;
}
