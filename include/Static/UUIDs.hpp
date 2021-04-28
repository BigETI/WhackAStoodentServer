#pragma once

#include <cstdint>
#include <span>
#include <vector>

#include <uuid.h>

namespace WhackAStoodentServer
{
	class UUIDs
	{
	public:

		static constexpr std::size_t DataSize = static_cast<std::size_t>(16);

		UUIDs() = delete;
		UUIDs(const UUIDs&) = delete;
		UUIDs(UUIDs&&) = delete;
		~UUIDs() = delete;

		static uuids::uuid& CreateNewUUID(uuids::uuid& result);
		
		static std::vector<std::uint8_t>& SerializeUUID(const uuids::uuid& uuid, std::vector<std::uint8_t>& result);

		static std::span<std::uint8_t const> DeserializeUUID(const std::span<std::uint8_t const>& bytes, uuids::uuid& result);

		UUIDs& operator=(const UUIDs&) = delete;
		UUIDs& operator=(UUIDs&&) = delete;
	};
}
