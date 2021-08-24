#pragma once

#include <memory>
#include <string>

#include <uuid.h>

#include <Misc/Peer.hpp>

namespace WhackAStoodentServer
{
	class User
	{
	public:

		Event<> OnConnected;

		Event<> OnDisconnected;

		Event<std::int32_t> OnPingReceived;

		Event<std::int32_t> OnPongReceived;

		Event<> OnMatchHistoryRequested;

		User() = delete;
		User(const User&) = delete;
		User(User&&) = delete;

		User(std::shared_ptr<Peer> peer, uuids::uuid userID, const std::wstring& name, const std::string& sessionCode, std::int64_t score);

		virtual ~User();

		virtual const Peer& GetPeer() const;

		virtual Peer& GetPeer();

		virtual const uuids::uuid& GetUserID() const;

		virtual const std::wstring& GetName() const;

		virtual void SetName(const std::wstring& newName);

		virtual const std::string& GetSessionCode() const;

		virtual void SetSessionCode(const std::string& newSessionCode);

		virtual void SetSessionCode(std::string&& newSessionCode);

		virtual void ResetSessionCode();

		virtual std::int64_t GetScore() const;

		virtual void SetScore(std::int64_t newScore);

	private:

		std::shared_ptr<Peer> peer;

		const uuids::uuid userID;

		std::wstring name;

		std::string sessionCode;

		std::int64_t score;
	};
}
