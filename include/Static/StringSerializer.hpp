#pragma once

#include <string>
#include <string_view>
#include <span>
#include <type_traits>
#include <vector>

#include <Exceptions/DeserializationFailedException.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a string serializer
	/// </summary>
	class StringSerializer
	{
	public:

		StringSerializer() = delete;
		StringSerializer(const StringSerializer&) = delete;
		StringSerializer(StringSerializer&&) = delete;
		~StringSerializer() = delete;

		/// <summary>
		/// Serializes string
		/// </summary>
		/// <typeparam name="TLength">String length type</typeparam>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		template <typename TLength, typename TCharacter>
		static std::vector<std::uint8_t>& Serialize(std::basic_string_view<TCharacter> string, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				std::is_same<std::uint8_t, TLength>::value ||
				std::is_same<std::uint16_t, TLength>::value ||
				std::is_same<std::uint32_t, TLength>::value ||
				std::is_same<std::uint64_t, TLength>::value
			);
			TLength string_length(static_cast<TLength>(string.length() & ~static_cast<TLength>(0)));
			std::size_t offset = result.size();
			result.resize(offset + sizeof(TLength) + (static_cast<std::size_t>(string_length) * sizeof(TCharacter)));
			std::memcpy(result.data() + offset, &string_length, sizeof(TLength));
			std::memcpy(result.data() + offset + sizeof(TLength), string.data(), static_cast<std::size_t>(string_length) * sizeof(TCharacter));
			return result;
		}

		/// <summary>
		/// Serializes byte sized string
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		template <typename TCharacter>
		static inline std::vector<std::uint8_t>& SerializeByteSizedString(std::basic_string_view<TCharacter> string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint8_t, TCharacter>(string, result);
		}

		/// <summary>
		/// Serializes byte sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeByteSizedString(std::string_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeByteSizedString<std::string_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes byte sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeByteSizedString(std::wstring_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeByteSizedString<std::wstring_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes short sized string
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		template <typename TCharacter>
		static inline std::vector<std::uint8_t>& SerializeShortSizedString(std::basic_string_view<TCharacter> string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint16_t, TCharacter>(string, result);
		}

		/// <summary>
		/// Serializes short sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeShortSizedString(std::string_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeShortSizedString<std::string_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes short sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeShortSizedString(std::wstring_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeShortSizedString<std::wstring_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes integer sized string
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		template <typename TCharacter>
		static inline std::vector<std::uint8_t>& SerializeIntegerSizedString(std::basic_string_view<TCharacter> string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint32_t, TCharacter>(string, result);
		}

		/// <summary>
		/// Serializes integer sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeIntegerSizedString(std::string_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeIntegerSizedString<std::string_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes integer sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeIntegerSizedString(std::wstring_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeIntegerSizedString<std::wstring_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes long sized string
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		template <typename TCharacter>
		static inline std::vector<std::uint8_t>& SerializeLongSizedString(std::basic_string_view<TCharacter> string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint64_t, TCharacter>(string, result);
		}

		/// <summary>
		/// Serializes long sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeLongSizedString(std::string_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeLongSizedString<std::string_view::value_type>(string, result);
		}

		/// <summary>
		/// Serializes long sized string
		/// </summary>
		/// <param name="string">String</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized string</returns>
		static inline std::vector<std::uint8_t>& SerializeLongSizedString(std::wstring_view string, std::vector<std::uint8_t>& result)
		{
			return SerializeLongSizedString<std::wstring_view::value_type>(string, result);
		}

		/// <summary>
		/// Deserializes string from given data
		/// </summary>
		/// <typeparam name="TLength">String length type</typeparam>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename TLength, typename TCharacter>
		static std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> bytes, std::basic_string<TCharacter>& result)
		{
			static_assert
			(
				std::is_same<std::uint8_t, TLength>::value ||
				std::is_same<std::uint16_t, TLength>::value ||
				std::is_same<std::uint32_t, TLength>::value ||
				std::is_same<std::uint64_t, TLength>::value
			);
			TLength string_length;
			std::span<const std::uint8_t> next_bytes(NumericSerializer::Deserialize<TLength>(bytes, string_length));
			std::size_t length(static_cast<std::size_t>(string_length));
			std::size_t size(length * sizeof(TCharacter));
			if (next_bytes.size() < size)
			{
				throw DeserializationFailedException();
			}
			result.resize(length);
			std::memcpy(result.data(), next_bytes.data(), size);
			return next_bytes.subspan(size, next_bytes.size() - size);
		}

		/// <summary>
		/// Deserializes byte sized string from given data
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename TCharacter>
		static inline std::span<const std::uint8_t> DeserializeByteSizedString(std::span<const std::uint8_t> bytes, std::basic_string<TCharacter>& result)
		{
			return Deserialize<std::uint8_t, TCharacter>(bytes, result);
		}

		/// <summary>
		/// Deserializes byte sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeByteSizedString(std::span<const std::uint8_t> bytes, std::string& result)
		{
			return DeserializeByteSizedString<std::string::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes byte sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeByteSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return DeserializeByteSizedString<std::wstring::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes short sized string from given data
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename TCharacter>
		static inline std::span<const std::uint8_t> DeserializeShortSizedString(std::span<const std::uint8_t> bytes, std::basic_string<TCharacter>& result)
		{
			return Deserialize<std::uint16_t, TCharacter>(bytes, result);
		}

		/// <summary>
		/// Deserializes short sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeShortSizedString(std::span<const std::uint8_t> bytes, std::string& result)
		{
			return DeserializeShortSizedString<std::string::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes short sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeShortSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return DeserializeShortSizedString<std::wstring::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer sized string from given data
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename TCharacter>
		static inline std::span<const std::uint8_t> DeserializeIntegerSizedString(std::span<const std::uint8_t> bytes, std::basic_string<TCharacter>& result)
		{
			return Deserialize<std::uint32_t, TCharacter>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeIntegerSizedString(std::span<const std::uint8_t> bytes, std::string& result)
		{
			return DeserializeIntegerSizedString<std::string::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeIntegerSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return DeserializeIntegerSizedString<std::wstring::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes long sized string from given data
		/// </summary>
		/// <typeparam name="TCharacter">String character type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		template <typename TCharacter>
		static inline std::span<const std::uint8_t> DeserializeLongSizedString(std::span<const std::uint8_t> bytes, std::basic_string<TCharacter>& result)
		{
			return Deserialize<std::uint64_t, TCharacter>(bytes, result);
		}

		/// <summary>
		/// Deserializes long sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeLongSizedString(std::span<const std::uint8_t> bytes, std::string& result)
		{
			return DeserializeLongSizedString<std::string::value_type>(bytes, result);
		}

		/// <summary>
		/// Deserializes long sized string from given data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static inline std::span<const std::uint8_t> DeserializeLongSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return DeserializeLongSizedString<std::wstring::value_type>(bytes, result);
		}

		StringSerializer& operator=(const StringSerializer&) = delete;
		StringSerializer& operator=(StringSerializer&&) = delete;
	};
}
