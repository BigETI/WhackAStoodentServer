#pragma once

#include <cstdint>
#include <span>
#include <type_traits>
#include <vector>

#include <Exceptions/DeserializationFailedException.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a numeric serializer
	/// </summary>
	class NumericSerializer
	{
	public:

		NumericSerializer() = delete;
		NumericSerializer(const NumericSerializer&) = delete;
		NumericSerializer(NumericSerializer&&) = delete;
		~NumericSerializer() = delete;

		/// <summary>
		/// Serializes number
		/// </summary>
		/// <typeparam name="T">Number type</typeparam>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized number</returns>
		template <typename T>
		static std::vector<std::uint8_t>& Serialize(T value, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				std::is_same<std::int8_t, T>::value ||
				std::is_same<std::uint8_t, T>::value ||
				std::is_same<std::int16_t, T>::value ||
				std::is_same<std::uint16_t, T>::value ||
				std::is_same<std::int32_t, T>::value ||
				std::is_same<std::uint32_t, T>::value ||
				std::is_same<std::int64_t, T>::value ||
				std::is_same<std::uint64_t, T>::value ||
				std::is_same<float, T>::value ||
				std::is_same<double, T>::value ||
				std::is_same<long double, T>::value
			);
			std::size_t offset(result.size());
			result.resize(offset + sizeof(T));
			std::memcpy(result.data() + offset, &value, sizeof(T));
			return result;
		}

		/// <summary>
		/// Serializes signed byte
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized signed byte</returns>
		static inline std::vector<std::uint8_t>& SerializeSignedByte(std::int8_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int8_t>(value, result);
		}

		/// <summary>
		/// Serializes byte
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized byte</returns>
		static inline std::vector<std::uint8_t>& SerializeByte(std::uint8_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint8_t>(value, result);
		}

		/// <summary>
		/// Serializes short
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized short</returns>
		static inline std::vector<std::uint8_t>& SerializeShort(std::int16_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int16_t>(value, result);
		}

		/// <summary>
		/// Serializes unsigned short
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized unsigned short</returns>
		static inline std::vector<std::uint8_t>& SerializeUnsignedShort(std::uint16_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint16_t>(value, result);
		}

		/// <summary>
		/// Serializes integer
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized integer</returns>
		static inline std::vector<std::uint8_t>& SerializeInteger(std::int32_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int32_t>(value, result);
		}

		/// <summary>
		/// Serializes unsigned integer
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized unsigned integer</returns>
		static inline std::vector<std::uint8_t>& SerializeUnsigedInteger(std::uint32_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint32_t>(value, result);
		}

		/// <summary>
		/// Serializes long
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized long</returns>
		static inline std::vector<std::uint8_t>& SerializeLong(std::int64_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int64_t>(value, result);
		}

		/// <summary>
		/// Serializes unsigned long
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized unsigned long</returns>
		static inline std::vector<std::uint8_t>& SerializeUnsignedLong(std::uint64_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint64_t>(value, result);
		}

		/// <summary>
		/// Serializes floating point number
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized floating point number</returns>
		static inline std::vector<std::uint8_t>& SerializeFloat(float value, std::vector<std::uint8_t>& result)
		{
			return Serialize<float>(value, result);
		}

		/// <summary>
		/// Serializes double sized floating point number
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized floating point number</returns>
		static inline std::vector<std::uint8_t>& SerializeDouble(double value, std::vector<std::uint8_t>& result)
		{
			return Serialize<double>(value, result);
		}

		/// <summary>
		/// Serializes long double sized floating point number
		/// </summary>
		/// <param name="value">Value</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized floating point number</returns>
		static inline std::vector<std::uint8_t>& SerializeLongDouble(long double value, std::vector<std::uint8_t>& result)
		{
			return Serialize<long double>(value, result);
		}

		/// <summary>
		/// Deserializes number from data
		/// </summary>
		/// <typeparam name="T">Number type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename T>
		static std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> bytes, T& result)
		{
			static_assert
			(
				std::is_same<std::int8_t, T>::value ||
				std::is_same<std::uint8_t, T>::value ||
				std::is_same<std::int16_t, T>::value ||
				std::is_same<std::uint16_t, T>::value ||
				std::is_same<std::int32_t, T>::value ||
				std::is_same<std::uint32_t, T>::value ||
				std::is_same<std::int64_t, T>::value ||
				std::is_same<std::uint64_t, T>::value ||
				std::is_same<float, T>::value ||
				std::is_same<double, T>::value ||
				std::is_same<long double, T>::value
			);
			if (bytes.size() < sizeof(T))
			{
				throw DeserializationFailedException();
			}
			std::memcpy(&result, bytes.data(), sizeof(T));
			return bytes.subspan<sizeof(T)>();
		}

		/// <summary>
		/// Deserializes signed byte from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeSignedByte(std::span<const std::uint8_t> bytes, std::int8_t& result)
		{
			return Deserialize<std::int8_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes byte from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeByte(std::span<const std::uint8_t> bytes, std::uint8_t& result)
		{
			return Deserialize<std::uint8_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes short from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeShort(std::span<const std::uint8_t> bytes, std::int16_t& result)
		{
			return Deserialize<std::int16_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes unsigned short from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeUnsignedShort(std::span<const std::uint8_t> bytes, std::uint16_t& result)
		{
			return Deserialize<std::uint16_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeInteger(std::span<const std::uint8_t> bytes, std::int32_t& result)
		{
			return Deserialize<std::int32_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes unsigned integer from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeUnsigedInteger(std::span<const std::uint8_t> bytes, std::uint32_t& result)
		{
			return Deserialize<std::uint32_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes long from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeLong(std::span<const std::uint8_t> bytes, std::int64_t& result)
		{
			return Deserialize<std::int64_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes unsigned long from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeUnsignedLong(std::span<const std::uint8_t> bytes, std::uint64_t& result)
		{
			return Deserialize<std::uint64_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes floating point number from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeFloat(std::span<const std::uint8_t> bytes, float& result)
		{
			return Deserialize<float>(bytes, result);
		}

		/// <summary>
		/// Deserializes double sized floating point number from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeDouble(std::span<const std::uint8_t> bytes, double& result)
		{
			return Deserialize<double>(bytes, result);
		}

		/// <summary>
		/// Deserializes long double sized floating point number from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeLongDouble(std::span<const std::uint8_t> bytes, long double& result)
		{
			return Deserialize<long double>(bytes, result);
		}

		NumericSerializer& operator=(const NumericSerializer&) = delete;
		NumericSerializer& operator=(NumericSerializer&&) = delete;
	};
}
