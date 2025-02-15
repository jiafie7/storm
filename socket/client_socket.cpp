#include "socket/client_socket.h"

using namespace storm::socket;

ClientSocket::ClientSocket(const std::string& ip, int port)
{
  connect(ip, port);
}

