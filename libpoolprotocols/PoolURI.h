#pragma once

#include <string>

// A simple URI parser specifically for mining pool enpoints
namespace dev
{

enum class SecureLevel {NONE = 0, TLS12, TLS, ALLOW_SELFSIGNED};
enum class ProtocolFamily {GETWORK = 0, STRATUM};

class URI
{
public:
	URI() {};
	URI(const std::string uri) { parse(uri); };
	URI(const char *uri) { parse(std::string(uri)); };

	URI &operator = (const std::string &uri) { parse(uri); return *this; };
	URI &operator = (const char *uri) { parse(std::string(uri)); return *this; };

	std::string Scheme() const;
	std::string Host() const;
	std::string Port() const;

	bool KnownScheme();
	static std::string KnownSchemes(ProtocolFamily family);
	ProtocolFamily ProtoFamily();
	unsigned ProtoVersion();
	SecureLevel ProtoSecureLevel();

private:
	void parse(const std::string &uri);

	std::string    m_scheme;
	std::string    m_host;
	std::string    m_port;
};

// inlines
inline std::string URI::Scheme() const
{
	return m_scheme;
}
	
inline std::string URI::Host() const
{
	return m_host;
}

inline std::string URI::Port() const
{
	return m_port;
}

}

