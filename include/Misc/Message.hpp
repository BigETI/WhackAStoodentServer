#pragma once

#include <cstdint>
#include <iostream>
#include <span>
#include <memory>
#include <vector>

#include <Enumerators/EMessageType.hpp>
#include <Exceptions/DeserializationFailedException.hpp>
#include <Interfaces/ISerializableMessage.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a message
	/// </summary>
	class Message
	{
	public:

		Message() = delete;
		Message(const Message&) = delete;
		Message(Message&&) = delete;

		/// <summary>
		/// Constructs a message
		/// </summary>
		/// <param name="data">Message data</param>
		Message(std::span<const std::uint8_t> data);

		/// <summary>
		/// Gets the message type
		/// </summary>
		/// <returns>Message type</returns>
		EMessageType GetMessageType() const;

		/// <summary>
		/// Gets message data
		/// </summary>
		/// <returns>Message data</returns>
		std::span<const std::uint8_t> GetData() const;

		/// <summary>
		/// Tries to get data
		/// </summary>
		/// <typeparam name="T">Message type</typeparam>
		/// <param name="result">Result</param>
		/// <returns>"true" if getting message data was successful, otherwise "false"</returns>
		template <typename T>
		bool TryGetData(T& result) const
		{
			static_assert(std::is_base_of<ISerializableMessage, T>::value);
			bool ret(true);
			try
			{
				result.Deserialize(data);
			}
			catch (const DeserializationFailedException& e)
			{
				ret = false;
				std::cerr << e.what() << std::endl;
			}
			return ret;
		}

	private:

		/// <summary>
		/// Message data
		/// </summary>
		std::vector<std::uint8_t> data;
	};
}
