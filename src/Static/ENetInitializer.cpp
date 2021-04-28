#include <enet/enet.h>

#include <Exceptions/ENetInitializationFailedException.hpp>
#include <Static/ENetInitializer.hpp>

std::size_t WhackAStoodentServer::ENetInitializer::initializationCount(static_cast<std::size_t>(0));

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

std::size_t WhackAStoodentServer::ENetInitializer::GetInitializationCount()
{
	return initializationCount;
}
