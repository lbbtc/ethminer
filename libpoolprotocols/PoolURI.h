#pragma once

#include <string>

// A simple URI parser specifically for mining pool enpoints
namespace dev
{

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

private:
	void toLower(std::string &str)
	{
		std::string::iterator end = str.end();
		for (std::string::iterator it = str.begin(); it != end; it++)
			*it = tolower(*it);
	}

	void parse(const std::string &uri)
	{
		m_scheme.clear();
		m_host.clear();
		m_port.clear();

		std::string u = uri;
		toLower(u);

		size_t pos = u.find("://");
		if (pos != std::string::npos) {
			if (pos < 3)
				return;
			m_scheme = u.substr(0, pos);
			u = u.substr(pos + 3);
		}

		pos = u.find(":");
		if (pos != std::string::npos) {
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

