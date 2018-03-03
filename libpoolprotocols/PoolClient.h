#ifndef POOL_CLIENT_H_
#define POOL_CLIENT_H_

#pragma once

#include <boost/asio/ip/address.hpp>

#include <libethcore/Farm.h>
#include <libethcore/Miner.h>
#include <libpoolprotocols/PoolURI.h>

using namespace std;

namespace dev
{
	namespace eth
	{
		class PoolConnection
		{
		public:
			PoolConnection() {};
			PoolConnection(const string &host, const string &port, const string &user, const string &pass, const SecureLevel secLevel, unsigned version)
				: m_host(host), m_port(port), m_user(user), m_pass(pass), m_secLevel(secLevel), m_version(version) {};
			string Host() const { return m_host; };
			string Port() const { return m_port; };
			string User() const { return m_user; };
			string Pass() const { return m_pass; };
			SecureLevel SecLevel() const { return m_secLevel; };
			boost::asio::ip::address Address() const { return m_address; };
			unsigned Version() const { return m_version; };
			

			void Host(string host) { m_host = host; };
			void Port(string port) { m_port = port; };
			void User(string user) { m_user = user; };
			void Pass(string pass) { m_pass = pass; };
			void SecLevel(SecureLevel secLevel) { m_secLevel = secLevel; };
			void Address(boost::asio::ip::address address) { m_address = address; };
			void Version(unsigned version) { m_version = version; };

		private:
		        string m_host;
       			string m_port;
			string m_user;
			string m_pass;
			SecureLevel m_secLevel = SecureLevel::NONE;
			boost::asio::ip::address m_address;
			unsigned m_version = 0;
		};

		class PoolClient
		{
		public:
			void setConnection(PoolConnection &conn);

			virtual void connect() = 0;
			virtual void disconnect() = 0;

			virtual void submitHashrate(string const & rate) = 0;
			virtual void submitSolution(Solution solution) = 0;
			virtual bool isConnected() = 0;

			using SolutionAccepted = std::function<void(bool const&)>;
			using SolutionRejected = std::function<void(bool const&)>;
			using Disconnected = std::function<void()>;
			using Connected = std::function<void()>;
			using WorkReceived = std::function<void(WorkPackage const&)>;

			void onSolutionAccepted(SolutionAccepted const& _handler) { m_onSolutionAccepted = _handler; }
			void onSolutionRejected(SolutionRejected const& _handler) { m_onSolutionRejected = _handler; }
			void onDisconnected(Disconnected const& _handler) { m_onDisconnected = _handler; }
			void onConnected(Connected const& _handler) { m_onConnected = _handler; }
			void onWorkReceived(WorkReceived const& _handler) { m_onWorkReceived = _handler; }

		protected:
			bool m_authorized = false;
			bool m_connected = false;
			PoolConnection m_conn;
			bool m_connection_changed = false;

			SolutionAccepted m_onSolutionAccepted;
			SolutionRejected m_onSolutionRejected;
			Disconnected m_onDisconnected;
			Connected m_onConnected;
			WorkReceived m_onWorkReceived;
		};
	}
}

#endif

