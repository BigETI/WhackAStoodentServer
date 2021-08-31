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
		/// A class that describes an authenticate message
		/// </summary>
		class AuthenticateMessage : public ASerializableMessage<EMessageType::Authenticate>
		{
		public:

			/// <summary>
			/// Constructs an authenticate message
			/// </summary>
			AuthenticateMessage();

			/// <summary>
			/// Constructs an authenticate message
			/// </summary>
			/// <param name="userID">User ID</param>
			/// <param name="username">Username</param>
			AuthenticateMessage(const uuids::uuid& userID, std::wstring_view username);

			/// <summary>
			/// Destroys authenticate message
			/// </summary>
			virtual ~AuthenticateMessage() override;

			/// <summary>
			/// Gets the user ID
			/// </summary>
			/// <returns>User ID</returns>
			virtual const uuids::uuid& GetUserID() const;

			/// <summary>
			/// Gets the username
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
			/// Username
			/// </summary>
			std::wstring username;
		};
	}
}
