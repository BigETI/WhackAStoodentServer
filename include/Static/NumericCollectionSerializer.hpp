#pragma once

#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

#include <span.hpp>

#include <Interfaces/ISerializable.hpp>
#include <Static/NumericSerializer.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a numeric collection serializer
	/// </summary>
	class NumericCollectionSerializer
	{
	public:

		NumericCollectionSerializer() = delete;
		NumericCollectionSerializer(const NumericCollectionSerializer&) = delete;
		NumericCollectionSerializer(NumericCollectionSerializer&&) = delete;
		~NumericCollectionSerializer() = delete;

		/// <summary>
		/// Serializes given numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <typeparam name="TLength">Length type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement, typename TLength>
		static std::vector<std::uint8_t>& Serialize(nonstd::span<const TElement> collection, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				(
					std::is_same<std::int8_t, TElement>::value ||
					std::is_same<std::uint8_t, TElement>::value ||
					std::is_same<std::int16_t, TElement>::value ||
					std::is_same<std::uint16_t, TElement>::value ||
					std::is_same<std::int32_t, TElement>::value ||
					std::is_same<std::uint32_t, TElement>::value ||
					std::is_same<std::int64_t, TElement>::value ||
					std::is_same<std::uint64_t, TElement>::value ||
					std::is_same<float, TElement>::value ||
					std::is_same<double, TElement>::value ||
					std::is_same<long double, TElement>::value
				) &&
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
			for (const TElement& element : nonstd::span<const TElement>(collection.begin(), collection.begin() + size))
			{
				NumericSerializer::Serialize<TElement>(element, result);
			}
			return result;
		}

		/// <summary>
		/// Serializes given numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <typeparam name="TLength">Length type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement, typename TLength>
		static std::vector<std::uint8_t>& Serialize(nonstd::span<const std::shared_ptr<TElement>> collection, std::vector<std::uint8_t>& result)
		{
			static_assert
			(
				(
					std::is_same<std::int8_t, TElement>::value ||
					std::is_same<std::uint8_t, TElement>::value ||
					std::is_same<std::int16_t, TElement>::value ||
					std::is_same<std::uint16_t, TElement>::value ||
					std::is_same<std::int32_t, TElement>::value ||
					std::is_same<std::uint32_t, TElement>::value ||
					std::is_same<std::int64_t, TElement>::value ||
					std::is_same<std::uint64_t, TElement>::value ||
					std::is_same<float, TElement>::value ||
					std::is_same<double, TElement>::value ||
					std::is_same<long double, TElement>::value
				) &&
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
			for (const std::shared_ptr<TElement>& element : nonstd::span<const TElement>(collection.begin(), collection.begin() + size))
			{
				NumericSerializer::Serialize<TElement>(*element, result);
			}
			return result;
		}

		/// <summary>
		/// Serializes byte sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeByteSizedCollection(nonstd::span<const TElement> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint8_t>(collection, result);
		}

		/// <summary>
		/// Serializes byte sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeByteSizedCollection(nonstd::span<const std::shared_ptr<TElement>> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint8_t>(collection, result);
		}

		/// <summary>
		/// Serializes short sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeShortSizedCollection(nonstd::span<const TElement> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint16_t>(collection, result);
		}

		/// <summary>
		/// Serializes short sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeShortSizedCollection(nonstd::span<const std::shared_ptr<TElement>> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint16_t>(collection, result);
		}

		/// <summary>
		/// Serializes integer sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeIntegerSizedCollection(nonstd::span<const TElement> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint32_t>(collection, result);
		}

		/// <summary>
		/// Serializes integer sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeIntegerSizedCollection(nonstd::span<const std::shared_ptr<TElement>> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint32_t>(collection, result);
		}

		/// <summary>
		/// Serializes long sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeLongSizedCollection(nonstd::span<const TElement> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint64_t>(collection, result);
		}

		/// <summary>
		/// Serializes long sized numeric collection
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="collection">Numeric collection</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized numeric collection</returns>
		template <typename TElement>
		static inline std::vector<std::uint8_t>& SerializeLongSizedCollection(nonstd::span<const std::shared_ptr<TElement>> collection, std::vector<std::uint8_t>& result)
		{
			return Serialize<TElement, std::uint64_t>(collection, result);
		}

		/// <summary>
		/// Deserializes numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <typeparam name="TLength">Length type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement, typename TLength>
		static nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> bytes, std::vector<TElement>& result)
		{
			static_assert
			(
				(
					std::is_same<std::uint8_t, TElement>::value ||
					std::is_same<std::uint16_t, TElement>::value ||
					std::is_same<std::uint32_t, TElement>::value ||
					std::is_same<std::uint64_t, TElement>::value
				) &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			TLength element_count;
			nonstd::span<const std::uint8_t> ret(NumericSerializer::Deserialize<TLength>(bytes, element_count));
			result.resize(static_cast<std::size_t>(element_count));
			for (TElement& element : result)
			{
				ret = NumericSerializer::Deserialize<TElement>(bytes, element);
			}
			return ret;
		}

		/// <summary>
		/// Deserializes numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <typeparam name="TLength">Length type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement, typename TLength>
		static nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			static_assert
			(
				(
					std::is_same<std::uint8_t, TElement>::value ||
					std::is_same<std::uint16_t, TElement>::value ||
					std::is_same<std::uint32_t, TElement>::value ||
					std::is_same<std::uint64_t, TElement>::value
				) &&
				(
					std::is_same<std::uint8_t, TLength>::value ||
					std::is_same<std::uint16_t, TLength>::value ||
					std::is_same<std::uint32_t, TLength>::value ||
					std::is_same<std::uint64_t, TLength>::value
				)
			);
			TLength element_count;
			nonstd::span<const std::uint8_t> ret(NumericSerializer::Deserialize<TLength>(bytes, element_count));
			result.resize(static_cast<std::size_t>(element_count));
			for (TElement& element : result)
			{
				element = std::make_shared<TElement>();
				ret = NumericSerializer::Deserialize<TElement>(bytes, *element);
			}
			return ret;
		}

		/// <summary>
		/// Deserializes byte sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeByteSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint8_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes byte sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeByteSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint8_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes short sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeShortSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint16_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes short sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeShortSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint16_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeIntegerSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint32_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes integer sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeIntegerSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint32_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes long sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeLongSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<TElement>& result)
		{
			return Deserialize<TElement, std::uint64_t>(bytes, result);
		}

		/// <summary>
		/// Deserializes long sized numeric collection from data
		/// </summary>
		/// <typeparam name="TElement">Element type</typeparam>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remeining data to be deserialized</returns>
		template <typename TElement>
		static inline nonstd::span<const std::uint8_t> DeserializeLongSizedCollection(nonstd::span<const std::uint8_t> bytes, std::vector<std::shared_ptr<TElement>>& result)
		{
			return Deserialize<TElement, std::uint64_t>(bytes, result);
		}

		NumericCollectionSerializer& operator=(const NumericCollectionSerializer&) = delete;
		NumericCollectionSerializer& operator=(NumericCollectionSerializer&&) = delete;
	};
}
