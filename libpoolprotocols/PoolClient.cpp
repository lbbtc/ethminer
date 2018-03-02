#include "PoolClient.h"

using namespace std;
using namespace dev;
using namespace eth;

void PoolClient::setConnection(PoolConnection &conn)
{
	m_conn = conn;
	m_connection_changed = true;
}
