#pragma once

#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializable.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// An interface that represents a serializable message
	/// </summary>
	class ISerializableMessage : ISerializable
	{
		/// <summary>
		/// Gets the message type
		/// </summary>
		/// <returns>Message type</returns>
		virtual EMessageType GetMessageType() const = 0;
	};
}
