#pragma once

#include <stdexcept>
#include <string>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes an ENet intialization failed exception
	/// </summary>
	class ENetInitializationFailedException : public std::runtime_error
	{
	public:

		ENetInitializationFailedException() = delete;

		/// <summary>
		/// Constructs an ENet intialization failed exception
		/// </summary>
		/// <param name="errorCode">Error code</param>
		ENetInitializationFailedException(int errorCode);

		/// <summary>
		/// Destroys ENet intialization failed exception
		/// </summary>
		virtual ~ENetInitializationFailedException() override;

		/// <summary>
		/// Gets the error code
		/// </summary>
		/// <returns>Error code</returns>
		virtual int GetErrorCode() const;

	private:

		/// <summary>
		/// Error code
		/// </summary>
		int errorCode;
	};
}
