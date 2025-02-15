#pragma once

#include "socket/socket.h"

namespace storm
{
  namespace socket
  {
    class ClientSocket : public Socket
    {
    public:
      ClientSocket() = delete;
      ClientSocket(const std::string& ip, int port);
      ~ClientSocket() = default;
    };
  }
}
