#pragma once

#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializable.hpp>

namespace WhackAStoodentServer
{
	class ISerializableMessage : ISerializable
	{
		virtual EMessageType GetMessageType() const = 0;
	};
}
