#pragma once

#include <string>
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
	class StringSerializer
	{
	public:

		StringSerializer() = delete;
		StringSerializer(const StringSerializer&) = delete;
		StringSerializer(StringSerializer&&) = delete;
		~StringSerializer() = delete;

		template <typename TLength>
		static std::vector<std::uint8_t>& Serialize(const std::wstring& string, std::vector<std::uint8_t>& result)
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
			result.resize(offset + sizeof(TLength) + (static_cast<std::size_t>(string_length) * sizeof(std::wstring::value_type)));
			std::memcpy(result.data() + offset, &string_length, sizeof(TLength));
			std::memcpy(result.data() + offset + sizeof(TLength), string.data(), static_cast<std::size_t>(string_length) * sizeof(std::wstring::value_type));
			return result;
		}

		static inline std::vector<std::uint8_t>& SerializeByteSizedString(const std::wstring& string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint8_t>(string, result);
		}

		static inline std::vector<std::uint8_t>& SerializeShortSizedString(const std::wstring& string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint32_t>(string, result);
		}

		static inline std::vector<std::uint8_t>& SerializeIntegerSizedString(const std::wstring& string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint32_t>(string, result);
		}

		static inline std::vector<std::uint8_t>& SerializeLongSizedString(const std::wstring& string, std::vector<std::uint8_t>& result)
		{
			return Serialize<std::uint64_t>(string, result);
		}

		template <typename TLength>
		static std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> bytes, std::wstring& result)
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
			std::size_t size(length * sizeof(std::wstring::value_type));
			if (next_bytes.size() < size)
			{
				throw DeserializationFailedException();
			}
			result.resize(length);
			std::memcpy(result.data(), next_bytes.data(), size);
			return next_bytes.subspan(size, next_bytes.size() - size);
		}

		static inline std::span<const std::uint8_t> DeserializeByteSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return Deserialize<std::uint8_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeShortSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return Deserialize<std::uint16_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeIntegerSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return Deserialize<std::uint32_t>(bytes, result);
		}

		static inline std::span<const std::uint8_t> DeserializeLongSizedString(std::span<const std::uint8_t> bytes, std::wstring& result)
		{
			return Deserialize<std::uint64_t>(bytes, result);
		}

		StringSerializer& operator=(const StringSerializer&) = delete;
		StringSerializer& operator=(StringSerializer&&) = delete;
	};
}
