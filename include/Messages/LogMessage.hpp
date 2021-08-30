#pragma once

#include <string>
#include <string_view>

#include <Abstract/ASerializableMessage.hpp>
#include <Enumerators/ELogLevel.hpp>

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
		/// A class that describes a log message
		/// </summary>
		class LogMessage : public ASerializableMessage<EMessageType::Log>
		{
		public:

			/// <summary>
			/// Constructs a log message
			/// </summary>
			LogMessage();

			/// <summary>
			/// Constructs a log message
			/// </summary>
			/// <param name="logLevel">Log level</param>
			/// <param name="logMessage">Log message</param>
			LogMessage(ELogLevel logLevel, std::wstring_view logMessage);

			/// <summary>
			/// Destroys log message
			/// </summary>
			virtual ~LogMessage() override;

			/// <summary>
			/// Gets the log level
			/// </summary>
			/// <returns>Log level</returns>
			virtual ELogLevel GetLogLevel() const;

			/// <summary>
			/// Gets the log message
			/// </summary>
			/// <returns>Log message</returns>
			virtual std::wstring_view GetLogMessage() const;

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
			virtual std::span<const std::uint8_t> Deserialize(std::span<const std::uint8_t> data) override;

		private:

			/// <summary>
			/// Log level
			/// </summary>
			ELogLevel logLevel;

			/// <summary>
			/// Log message
			/// </summary>
			std::wstring logMessage;
		};
	}
}
