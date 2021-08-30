#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Whack-A-Stoodent server messages namespace
	/// </summary>
	namespace Messages
	{
		/// <summary>
		/// An abstract class that describes a serializable message
		/// </summary>
		template <EMessageType _MessageType>
		class ASerializableMessage : ISerializableMessage
		{
		public:

			/// <summary>
			/// Message type
			/// </summary>
			static constexpr const EMessageType MessageType = _MessageType;

			/// <summary>
			/// Constructs a serializable message
			/// </summary>
			ASerializableMessage()
			{
				// ...
			}

			/// <summary>
			/// Destroys serializable message
			/// </summary>
			virtual ~ASerializableMessage()
			{
				// ...
			}

			/// <summary>
			/// Gets the message type
			/// </summary>
			/// <returns>Message type</returns>
			virtual EMessageType GetMessageType() const override
			{
				return MessageType;
			}

			/// <summary>
			/// Serializes contents
			/// </summary>
			/// <param name="result">Result</param>
			/// <returns>Serialized contents</returns>
			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override
			{
				result.push_back(static_cast<std::uint8_t>(MessageType));
				return result;
			}

			/// <summary>
			/// Deserializes given input
			/// </summary>
			/// <param name="data">Data to deserialize</param>
			/// <returns>Remaining data to deserialize</returns>
			virtual std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> data) override
			{
				std::uint8_t message_type;
				std::span<const std::uint8_t> ret(NumericSerializer::DeserializeByte(data, message_type));
				if (MessageType != static_cast<EMessageType>(message_type))
				{
					throw DeserializationFailedException();
				}
				return ret;
			}
		};
	}
}
