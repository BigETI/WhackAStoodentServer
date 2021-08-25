#pragma once

#include <stdexcept>
#include <string>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a deserialization failed exception
	/// </summary>
	class DeserializationFailedException : public std::runtime_error
	{
	public:

		/// <summary>
		/// Constructs a deserialization exception
		/// </summary>
		DeserializationFailedException();

		/// <summary>
		/// Destroys deserialization exception
		/// </summary>
		virtual ~DeserializationFailedException();
	};
}
