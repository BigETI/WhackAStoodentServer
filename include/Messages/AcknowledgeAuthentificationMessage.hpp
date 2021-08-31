#pragma once

#include <string>
#include <string_view>

#include <uuid.h>

#include <Abstract/ASerializableMessage.hpp>

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
		/// A class that describes an acknowledge authentification message
		/// </summary>
		class AcknowledgeAuthentificationMessage : public ASerializableMessage<EMessageType::AcknowledgeAuthentification>
		{
		public:

			/// <summary>
			/// Constructs an acknowledge authentification message
			/// </summary>
			AcknowledgeAuthentificationMessage();

			/// <summary>
			/// Constructs an acknowledge authentification message
			/// </summary>
			/// <param name="userID">User ID</param>
			/// <param name="sessionCode">Session code</param>
			/// <param name="username">Username</param>
			AcknowledgeAuthentificationMessage(const uuids::uuid& userID, std::string_view sessionCode, std::wstring_view username);

			/// <summary>
			/// Destroys acknowledge authentification message
			/// </summary>
			virtual ~AcknowledgeAuthentificationMessage() override;

			/// <summary>
			/// Gets the user ID
			/// </summary>
			/// <returns>User ID</returns>
			virtual const uuids::uuid& GetUserID() const;

			/// <summary>
			/// Gets the session code
			/// </summary>
			/// <returns>Session code</returns>
			virtual std::string_view GetSessionCode() const;

			/// <summary>
			/// Gets the user name
			/// </summary>
			/// <returns>Username</returns>
			virtual std::wstring_view GetUsername() const;

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
			/// User ID
			/// </summary>
			uuids::uuid userID;

			/// <summary>
			/// Session code
			/// </summary>
			std::string sessionCode;

			/// <summary>
			/// Username
			/// </summary>
			std::wstring username;
		};
	}
}
