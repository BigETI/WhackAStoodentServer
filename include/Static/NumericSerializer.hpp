#pragma once

#include <cstdint>
#include <span>
#include <type_traits>
#include <vector>

#include <Exceptions/DeserializationFailedException.hpp>

namespace WhackAStoodentServer
{
	class NumericSerializer
	{
	public:

		NumericSerializer() = delete;
		NumericSerializer(const NumericSerializer&) = delete;
		NumericSerializer(NumericSerializer&&) = delete;
		~NumericSerializer() = delete;

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

		static inline std::vector<std::uint8_t>& SerializeSignedByte(std::int8_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int8_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeByte(std::uint8_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint8_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeShort(std::int16_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int16_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeUnsignedShort(std::uint16_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint16_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeInteger(std::int32_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int32_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeUnsigedInteger(std::uint32_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint32_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeLong(std::int64_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::int64_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeUnsignedLong(std::uint64_t value, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint64_t>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeFloat(float value, std::vector<std::uint8_t>& result)
		{
			return Serialize<float>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeDouble(double value, std::vector<std::uint8_t>& result)
		{
			return Serialize<double>(value, result);
		}

		static inline std::vector<std::uint8_t>& SerializeLongDouble(long double value, std::vector<std::uint8_t>& result)
		{
			return Serialize<long double>(value, result);
		}

		template <typename T>
		static std::span<const std::uint8_t> Deserialize(const std::span<const std::uint8_t>& bytes, T& result)
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

		static inline std::span<const std::uint8_t> DeserializeSignedByte(const std::span<const std::uint8_t>& bytes, std::int8_t& result)
		{
			return Deserialize<std::int8_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeByte(const std::span<const std::uint8_t>& bytes, std::uint8_t& result)
		{
			return Deserialize<std::uint8_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeShort(const std::span<const std::uint8_t>& bytes, std::int16_t& result)
		{
			return Deserialize<std::int16_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeUnsignedShort(const std::span<const std::uint8_t>& bytes, std::uint16_t& result)
		{
			return Deserialize<std::uint16_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeInteger(const std::span<const std::uint8_t>& bytes, std::int32_t& result)
		{
			return Deserialize<std::int32_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeUnsigedInteger(const std::span<const std::uint8_t>& bytes, std::uint32_t& result)
		{
			return Deserialize<std::uint32_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeLong(const std::span<const std::uint8_t>& bytes, std::int64_t& result)
		{
			return Deserialize<std::int64_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeUnsignedLong(const std::span<const std::uint8_t>& bytes, std::uint64_t& result)
		{
			return Deserialize<std::uint64_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeFloat(const std::span<const std::uint8_t>& bytes, float& result)
		{
			return Deserialize<float>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeDouble(const std::span<const std::uint8_t>& bytes, double& result)
		{
			return Deserialize<double>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeLongDouble(const std::span<const std::uint8_t>& bytes, long double& result)
		{
			return Deserialize<long double>(bytes, result);
		}

		NumericSerializer& operator=(const NumericSerializer&) = delete;
		NumericSerializer& operator=(NumericSerializer&&) = delete;
	};
}
