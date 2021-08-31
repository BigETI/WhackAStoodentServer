#pragma once

#include <cstdint>
#include <vector>

#include <span.hpp>
#include <uuid.h>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that provides functionalities for UUIDs
	/// </summary>
	class UUIDs
	{
	public:

		/// <summary>
		/// Data size
		/// </summary>
		static constexpr const std::size_t DataSize = static_cast<const std::size_t>(16);

		UUIDs() = delete;
		UUIDs(const UUIDs&) = delete;
		UUIDs(UUIDs&&) = delete;
		~UUIDs() = delete;

		/// <summary>
		/// Creates a new UUID
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>New UUID</returns>
		static uuids::uuid& CreateNewUUID(uuids::uuid& result);
		
		/// <summary>
		/// Serializes UUID
		/// </summary>
		/// <param name="uuid">UUID</param>
		/// <param name="result">Result</param>
		/// <returns>Serialized UUID</returns>
		static std::vector<std::uint8_t>& SerializeUUID(const uuids::uuid& uuid, std::vector<std::uint8_t>& result);

		/// <summary>
		/// Deserializes UUID from data
		/// </summary>
		/// <param name="bytes">Data</param>
		/// <param name="result">Result</param>
		/// <returns>Remaining data to be deserialized</returns>
		static nonstd::span<const std::uint8_t> DeserializeUUID(nonstd::span<const std::uint8_t> bytes, uuids::uuid& result);

		UUIDs& operator=(const UUIDs&) = delete;
		UUIDs& operator=(UUIDs&&) = delete;
	};
}
