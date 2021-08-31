#pragma once

#include <cstdint>
#include <vector>

#include <span.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// An interface that represents a serializable object
	/// </summary>
	class ISerializable
	{
	public:

		/// <summary>
		/// Serializes contents
		/// </summary>
		/// <param name="result">Result</param>
		/// <returns>Serialized contents</returns>
		virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const = 0;

		/// <summary>
		/// Deserializes given input
		/// </summary>
		/// <param name="data">Data to deserialize</param>
		/// <returns>Remaining data to deserialize</returns>
		virtual nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> data) = 0;
	};
}
