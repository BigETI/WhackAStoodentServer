#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include <enet/enet.h>
#include <uuid.h>

#include <Misc/Event.hpp>
#include <Misc/Message.hpp>
#include <Misc/User.hpp>

namespace WhackAStoodentServer
{
	class Server
	{
	public:

		Event<std::shared_ptr<Peer>> OnPeerConnectionAttempted;

		Event<std::shared_ptr<Peer>> OnPeerDisconnected;

		Event<std::shared_ptr<User>> OnUserConnected;

		Event<std::shared_ptr<User>> OnUserDisconnected;

		Event<std::shared_ptr<Message>> OnPeerMessageReceived;

		Event<std::shared_ptr<User>> OnUserAuthenticated;

		Event<std::shared_ptr<User>, std::int32_t> OnUserPingReceived;

		Event<std::shared_ptr<User>, std::int32_t> OnUserPongReceived;

		Server() = delete;

		Server(std::uint16_t port, std::uint32_t timeoutTime);

		virtual ~Server();

		bool Start();

		void Stop();

		bool IsRunning() const;

		bool ProcessMessages();

	private:

		std::uint16_t port;

		std::uint32_t timeoutTime;

		ENetHost* enetHost;

		std::unordered_map<std::uint16_t, std::shared_ptr<Peer>> peers;

		std::unordered_map<std::uint16_t, std::shared_ptr<User>> users;

		std::unordered_map<uuids::uuid, std::uint16_t> userIDToPeerIDLookup;
	};
}