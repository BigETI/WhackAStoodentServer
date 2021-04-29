#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <Enumerators/EMessageType.hpp>
#include <Exceptions/DeserializationFailedException.hpp>
#include <Interfaces/ISerializableMessage.hpp>

namespace WhackAStoodentServer
{
	class Message
	{
	public:

		Message() = delete;
		Message(const Message&) = delete;
		Message(Message&&) = delete;

		Message(const std::vector<std::uint8_t>& data);

		Message(std::uint8_t *data, std::size_t size);

		EMessageType GetMessageType() const;

		std::vector<std::uint8_t>& GetData(std::vector<std::uint8_t>& result) const;

		std::size_t GetDataSize() const;

		template <typename T>
		bool TryGetData(T& result) const
		{
			static_assert(std::is_base_of<ISerializableMessage, T>::value);
			bool ret(true);
			try
			{
				std::vector<std::uint8_t> data;
				result.Deserialize(GetData(data));
			}
			catch (const DeserializationFailedException& e)
			{
				ret = false;
				std::cerr << e.what() << std::endl;
			}
			return ret;
		}

	private:

		std::vector<std::uint8_t> data;
	};
}
