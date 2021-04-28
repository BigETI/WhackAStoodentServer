#pragma once

#include <cstdint>
#include <span>
#include <vector>

namespace WhackAStoodentServer
{
	class ISerializable
	{
	public:

		virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const = 0;

		virtual std::span<std::uint8_t const> Deserialize(const std::span<std::uint8_t const>& data) = 0;
	};
}
