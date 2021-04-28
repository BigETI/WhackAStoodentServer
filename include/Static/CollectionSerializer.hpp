#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <type_traits>
#include <vector>

#include <Interfaces/ISerializable.hpp>
#include <Static/NumericSerializer.hpp>

namespace WhackAStoodentServer
{
	class CollectionSerializer
	{
	public:

		CollectionSerializer() = delete;
		CollectionSerializer(const CollectionSerializer&) = delete;
		CollectionSerializer(CollectionSerializer&&) = delete;
		~CollectionSerializer() = delete;

		template <typename TElement, typename TLength>
		static std::vector<std::uint8_t>& Serialize(const std::span<const TElement>& collection, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				std::is_base_of<ISerializable, TElement>::value &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			std::size_t size(collection.size() & ~static_cast<TLength>(0));
			TLength element_count(static_cast<TLength>(size));
			NumericSerializer::Serialize<TLength>(element_count, result);
			for (const TElement& element : std::span<const TElement>(collection.begin(), collection.begin() + size))
			{
				element.Serialize(result);
			}
			return result;
		}

		template <typename TElement, typename TLength>
		static std::vector<std::uint8_t>& Serialize(const std::span<const std::shared_ptr<TElement>>& collection, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				std::is_base_of<ISerializable, TElement>::value &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			std::size_t size(collection.size() & ~static_cast<TLength>(0));
			TLength element_count(static_cast<TLength>(size));
			NumericSerializer::Serialize<TLength>(element_count, result);
			for (const std::shared_ptr<TElement>& element : std::span<const TElement>(collection.begin(), collection.begin() + size))
			{
				element->Serialize(result);
			}
			return result;
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeByteCollection(const std::span<const TElement>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint8_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeByteCollection(const std::span<const std::shared_ptr<TElement>>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint8_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeShortCollection(const std::span<const TElement>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint16_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeShortCollection(const std::span<const std::shared_ptr<TElement>>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint16_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeIntegerCollection(const std::span<const TElement>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint32_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeIntegerCollection(const std::span<const std::shared_ptr<TElement>>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint32_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeLongCollection(const std::span<const TElement>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint64_t>(collection, result);
		}

		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeLongCollection(const std::span<const std::shared_ptr<TElement>>& collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint64_t>(collection, result);
		}

		template <typename TElement, typename TLength>
		static std::span<const std::uint8_t> Deserialize(const std::span<const std::uint8_t>& bytes, std::vector<TElement>& result)
		{
			static_assert
			(
				std::is_base_of<ISerializable, TElement>::value &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			TLength element_count;
			std::span<const std::uint8_t> ret(NumericSerializer::Deserialize<TLength>(bytes, element_count));
			result.resize(static_cast<std::size_t>(element_count));
			for (TElement& element : result)
			{
				ret = element.Deserialize(bytes);
			}
			return ret;
		}

		template <typename TElement, typename TLength>
		static std::span<const std::uint8_t> Deserialize(const std::span<const std::uint8_t>& bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			static_assert
			(
				std::is_base_of<ISerializable, TElement>::value &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			TLength element_count;
			std::span<const std::uint8_t> ret(NumericSerializer::Deserialize<TLength>(bytes, element_count));
			result.resize(static_cast<std::size_t>(element_count));
			for (TElement& element : result)
			{
				element = std::make_shared<TElement>();
				ret = element.Deserialize(bytes);
			}
			return ret;
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeByteCollection(const std::span<const std::uint8_t>& bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint8_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeByteCollection(const std::span<const std::uint8_t>& bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint8_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeShortCollection(const std::span<const std::uint8_t>& bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint16_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeShortCollection(const std::span<const std::uint8_t>& bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint16_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeIntegerCollection(const std::span<const std::uint8_t>& bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint32_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeIntegerCollection(const std::span<const std::uint8_t>& bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint32_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeLongCollection(const std::span<const std::uint8_t>& bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint64_t>(bytes, result);
		}

		template <typename TElement>
		static inline std::span<const std::uint8_t> DeserializeLongCollection(const std::span<const std::uint8_t>& bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint64_t>(bytes, result);
		}

		CollectionSerializer& operator=(const CollectionSerializer&) = delete;
		CollectionSerializer& operator=(CollectionSerializer&&) = delete;
	};
}
