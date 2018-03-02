#ifndef POOL_CLIENT_H_
#define POOL_CLIENT_H_

#pragma once

#include <libethcore/Farm.h>
#include <libethcore/Miner.h>

using namespace std;

namespace dev
{
	namespace eth
	{
		class PoolConnection
		{
		public:
			typedef enum {
				STRATUM = 0,
				ETHPROXY,
				ETHEREUMSTRATUM
			} StratumProtocol;

			PoolConnection() {};
			PoolConnection(const string &host, const string &port, const string &user, const string &pass, const string &scheme, StratumProtocol proto)
				: m_host(host), m_port(port), m_user(user), m_pass(pass), m_scheme(scheme), m_proto(proto) {};
			string Host() const { return m_host; };
			string Port() const { return m_port; };
			string User() const { return m_user; };
			string Pass() const { return m_pass; };
			string Scheme() const { return m_scheme; };
			StratumProtocol Proto() const { return m_proto; };
			

			void Host(string host) { m_host = host; };
			void Port(string port) { m_port = port; };
			void User(string user) { m_user = user; };
			void Pass(string pass) { m_pass = pass; };
			void Scheme(string scheme) {m_scheme = scheme; };
			void Scheme(StratumProtocol proto) {m_proto = proto; };

		private:
		        string m_host;
       			string m_port;
			string m_user;
			string m_pass;
			string m_scheme;
			StratumProtocol m_proto;
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

