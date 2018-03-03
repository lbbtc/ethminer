#include <libpoolprotocols/PoolURI.h>
#include <map>

using namespace dev;
using namespace std;

static void toLower(string &str)
{
	string::iterator end = str.end();
	for (string::iterator it = str.begin(); it != end; it++)
		*it = tolower(*it);
}

typedef struct {
	ProtocolFamily family;
	SecureLevel secure;
	unsigned version;
} SchemeType;

static map<string, SchemeType> s_schemes = {
	{"stratum+tcp",	{ProtocolFamily::STRATUM, SecureLevel::NONE,  0}},
	{"stratum1+tcp",{ProtocolFamily::STRATUM, SecureLevel::NONE,  1}},
	{"stratum2+tcp",{ProtocolFamily::STRATUM, SecureLevel::NONE,  2}},
	{"stratum+tls",	{ProtocolFamily::STRATUM, SecureLevel::TLS12, 0}},
	{"stratum1+tls",{ProtocolFamily::STRATUM, SecureLevel::TLS12, 1}},
	{"stratum2+tls",{ProtocolFamily::STRATUM, SecureLevel::TLS12, 2}},
	{"stratum+ssl",	{ProtocolFamily::STRATUM, SecureLevel::TLS12, 0}},
	{"stratum1+ssl",{ProtocolFamily::STRATUM, SecureLevel::TLS12, 1}},
	{"stratum2+ssl",{ProtocolFamily::STRATUM, SecureLevel::TLS12, 2}},
	{"getwork+rpc",	{ProtocolFamily::GETWORK, SecureLevel::NONE,  0}},
	{"getwork+ssl",	{ProtocolFamily::GETWORK, SecureLevel::TLS12, 0}},
	{"getwork+tls",	{ProtocolFamily::GETWORK, SecureLevel::TLS12, 0}}
};

bool URI::KnownScheme()
{
	return s_schemes.find(m_scheme) != s_schemes.end();
}

ProtocolFamily URI::ProtoFamily()
{
	return s_schemes[m_scheme].family;
}

unsigned URI::ProtoVersion()
{
	return s_schemes[m_scheme].version;
}

SecureLevel URI::ProtoSecureLevel()
{
	return s_schemes[m_scheme].secure;
}

string URI::KnownSchemes(ProtocolFamily family)
{
	string schemes;
	for(const auto&s : s_schemes)
		if (s.second.family == family)
			schemes += s.first + " ";
	return schemes;
}

void URI::parse(const string &uri)
{
	m_scheme.clear();
	m_host.clear();
	m_port.clear();

	string u = uri;
	toLower(u);

	size_t pos = u.find("://");
	if (pos != string::npos) {
		if (pos < 3)
			return;
		m_scheme = u.substr(0, pos);
		u = u.substr(pos + 3);
	}

	pos = u.find(":");
	if (pos != string::npos) {
		if (pos < 1)
			return;
		m_host = u.substr(0, pos);
		u = u.substr(pos + 1);
	}
	else {
		m_host = u;
		return;
	}
	m_port = u;
}

