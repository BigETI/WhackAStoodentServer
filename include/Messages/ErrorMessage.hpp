#pragma once

#include <string>
#include <string_view>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/EErrorType.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// Whack-A-Stoodent server messages namespace
	/// </summary>
	namespace Messages
	{
		/// <summary>
		/// A class that describes an error message
		/// </summary>
		class ErrorMessage : public ASerializableMessage<EMessageType::Error>
		{
		public:

			/// <summary>
			/// Constructs an error message
			/// </summary>
			ErrorMessage();

			/// <summary>
			/// Constructs an error message
			/// </summary>
			/// <param name="errorType">Error type</param>
			/// <param name="errorMessage">Error message</param>
			ErrorMessage(EErrorType errorType, std::wstring_view errorMessage);

			/// <summary>
			/// Destroys error message
			/// </summary>
			virtual ~ErrorMessage() override;

			/// <summary>
			/// Gets the error type
			/// </summary>
			/// <returns>Error type</returns>
			virtual EErrorType GetErrorType() const;

			/// <summary>
			/// Gets the error message
			/// </summary>
			/// <returns>Error message</returns>
			virtual std::wstring_view GetErrorMessage() const;

			/// <summary>
			/// Serializes contents
			/// </summary>
			/// <param name="result">Result</param>
			/// <returns>Serialized contents</returns>
			virtual std::vector<std::uint8_t>& Serialize(std::vector<std::uint8_t>& result) const override;

			/// <summary>
			/// Deserializes given input
			/// </summary>
			/// <param name="data">Data to deserialize</param>
			/// <returns>Remaining data to deserialize</returns>
			virtual nonstd::span<const std::uint8_t> Deserialize(nonstd::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Error type
			/// </summary>
			EErrorType errorType;

			/// <summary>
			/// Error message
			/// </summary>
			std::wstring errorMessage;
		};
	}
}
