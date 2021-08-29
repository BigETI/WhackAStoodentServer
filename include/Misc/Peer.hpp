#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include <enet.h>

#include <Enumerators/EDisconnectionReason.hpp>
#include <Enumerators/EErrorType.hpp>
#include <Enumerators/EMessageType.hpp>
#include <Interfaces/ISerializableMessage.hpp>
#include <Misc/Event.hpp>
#include <Misc/Message.hpp>

/// <summary>
/// Whack-A-Stoodent server namespace
/// </summary>
namespace WhackAStoodentServer
{
	/// <summary>
	/// A class that describes a peer
	/// </summary>
	class Peer
	{
	public:

		/// <summary>
		/// Gets invoked when a connection was attempted
		/// </summary>
		Event<> OnConnectionAttempted;

		/// <summary>
		/// Gets invoked when peer has connected
		/// </summary>
		Event<> OnConnected;

		/// <summary>
		/// Gets invoked when peer has disconnected
		/// </summary>
		Event<> OnDisconnected;

		/// <summary>
		/// Gets invoked when an unsupported message type has been received
		/// </summary>
		Event<EMessageType> OnUnsupportedMessageTypeReceived;

		/// <summary>
		/// Gets invoked when a message has been received
		/// </summary>
		Event<std::shared_ptr<Message>> OnMessageReceived;

		/// <summary>
		/// Gets invoked when an error has been received
		/// </summary>
		Event<EErrorType, std::wstring_view> OnErrorReceived;

		Peer() = delete;
		Peer(const Peer&) = delete;
		Peer(Peer&&) = delete;

		/// <summary>
		/// Constructs a new peer
		/// </summary>
		/// <param name="peer">ENet peer</param>
		Peer(ENetPeer* peer);

		/// <summary>
		/// Destroys peer
		/// </summary>
		virtual ~Peer();

		/// <summary>
		/// Gets the incoming peer ID
		/// </summary>
		/// <returns>Incoming peer ID</returns>
		virtual std::uint16_t GetIncomingPeerID() const;

		/// <summary>
		/// Gets the outgoing peer ID
		/// </summary>
		/// <returns>Outgoing peer ID</returns>
		virtual std::uint16_t GetOutgoingPeerID() const;

		/// <summary>
		/// Gets the IP address string
		/// </summary>
		/// <returns>IP address string</returns>
		virtual std::string_view GetIPAddressString() const;

		/// <summary>
		/// Sends message to peer
		/// </summary>
		/// <typeparam name="T">Message type</typeparam>
		/// <typeparam name="...TArguments">Message argument types</typeparam>
		/// <param name="...arguments">Message arguments</param>
		template <typename T, typename... TArguments>
		void SendPeerMessage(TArguments... arguments)
		{
			static_assert(std::is_base_of<ISerializableMessage, T>::value);
			T message(arguments...);
			std::vector<std::uint8_t> data;
			SendPeerMessage(message.Serialize(data));
		}

		/// <summary>
		/// Sends a peer message
		/// </summary>
		/// <param name="data">Data</param>
		virtual void SendPeerMessage(const std::vector<uint8_t>& data);

		/// <summary>
		/// Disconnects peer
		/// </summary>
		/// <param name="reason">Disconnection reason</param>
		virtual void Disconnect(EDisconnectionReason reason);

		Peer& operator=(const Peer&) = delete;
		Peer& operator=(Peer&&) = delete;

	private:

		/// <summary>
		/// ENet peer
		/// </summary>
		ENetPeer* peer;

		/// <summary>
		/// IP address string
		/// </summary>
		std::string ipAddressString;
	};
}
