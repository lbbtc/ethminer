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
	URI::ProtocolFamily family;
	unsigned secure;
	unsigned version;
} SchemeType;

static map<string, SchemeType> s_schemes = {
	{"stratum", {URI::ProtocolFamily::STRATUM, 0, 0}},
	{"stratum1", {URI::ProtocolFamily::STRATUM, 0, 1}},
	{"stratum2", {URI::ProtocolFamily::STRATUM, 0, 2}},
	{"stratum+tcp", {URI::ProtocolFamily::STRATUM, 0, 0}},
	{"stratum1+tcp", {URI::ProtocolFamily::STRATUM, 0, 1}},
	{"stratum2+tcp", {URI::ProtocolFamily::STRATUM, 0, 2}},
	{"stratum+tls", {URI::ProtocolFamily::STRATUM, 2, 0}},
	{"stratum1+tls", {URI::ProtocolFamily::STRATUM, 2, 1}},
	{"stratum2+tls", {URI::ProtocolFamily::STRATUM, 2, 2}},
	{"stratum+ssl", {URI::ProtocolFamily::STRATUM, 2, 0}},
	{"stratum1+ssl", {URI::ProtocolFamily::STRATUM, 2, 1}},
	{"stratum2+ssl", {URI::ProtocolFamily::STRATUM, 2, 2}},
	{"http", {URI::ProtocolFamily::GETWORK, 0, 0}},
	{"https", {URI::ProtocolFamily::GETWORK, 2, 0}},
	{"http+tls", {URI::ProtocolFamily::GETWORK, 2, 0}},
	{"http+ssl", {URI::ProtocolFamily::GETWORK, 2, 0}}
};

bool URI::KnownScheme()
{
	return s_schemes.find(m_scheme) != s_schemes.end();
}

URI::ProtocolFamily URI::ProtoFamily()
{
	return s_schemes[m_scheme].family;
}

unsigned URI::ProtoVersion()
{
	return s_schemes[m_scheme].version;
}

unsigned URI::ProtoSecure()
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

