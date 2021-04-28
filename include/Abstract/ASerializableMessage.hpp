#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Static/NumericSerializer.hpp>

namespace WhackAStoodentServer
{
	namespace Messages
	{
		template <EMessageType _MessageType>
		class ASerializableMessage : ISerializableMessage
		{
		public:

			static constexpr EMessageType MessageType = _MessageType;

			ASerializableMessage()
			{
				// ...
			}

			virtual ~ASerializableMessage()
			{
				// ...
			}

			virtual EMessageType GetMessageType() const override
			{
				return MessageType;
			}

			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override
			{
				result.push_back(static_cast<std::uint8_t>(MessageType));
				return result;
			}

			virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) override
			{
				std::uint8_t message_type;
				std::span<std::uint8_t const> ret(NumericSerializer::DeserializeByte(data, message_type));
				if (MessageType != static_cast<EMessageType>(message_type))
				{
					throw DeserializationFailedException();
				}
				return ret;
			}
		};
	}
}
