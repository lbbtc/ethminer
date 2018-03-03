#include <map>
#include <boost/optional/optional_io.hpp>
#include <libpoolprotocols/PoolURI.h>

using namespace dev;
using namespace std;

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

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

URI::URI(const std::string uri)
{
	std::string u = uri;
	if (u.find("://") == std::string::npos)
		u = std::string("notspecified://") + u;
	m_uri = network::uri(u);
}

bool URI::KnownScheme()
{
	stringstream ss;
	ss << m_uri.scheme();
	std::string s = ss.str();
	trim(s);
	return s_schemes.find(s) != s_schemes.end();
}

ProtocolFamily URI::ProtoFamily()
{
	stringstream ss;
	ss << m_uri.scheme();
	std::string s = ss.str();
	trim(s);
	return s_schemes[s].family;
}

unsigned URI::ProtoVersion()
{
	stringstream ss;
	ss << m_uri.scheme();
	std::string s = ss.str();
	trim(s);
	return s_schemes[s].version;
}

SecureLevel URI::ProtoSecureLevel()
{
	stringstream ss;
	ss << m_uri.scheme();
	std::string s = ss.str();
	trim(s);
	return s_schemes[s].secure;
}

string URI::KnownSchemes(ProtocolFamily family)
{
	std::string schemes;
	for(const auto&s : s_schemes)
		if (s.second.family == family)
			schemes += s.first + " ";
	trim(schemes);
	return schemes;
}

string URI::Scheme() const
{
	stringstream ss;
	ss << m_uri.scheme();
	std::string s(ss.str());
	trim(s);
	return s;
}

string URI::Host() const
{
	stringstream ss;
	ss << m_uri.host();
	std::string s(ss.str());
	trim(s);
	return s;
}

string URI::Port() const
{
	stringstream ss;
	ss << m_uri.port();
	std::string s(ss.str());
	trim(s);
	return s;
}

string URI::UserInfo() const
{
	stringstream ss;
	ss << m_uri.user_info();
	std::string s(ss.str());
	trim(s);
	return s;
}

