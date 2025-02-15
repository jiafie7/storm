#pragma once

#include "socket/socket.h"

using namespace storm::socket;

namespace storm
{
  namespace task
  {
    class EchoTask
    {
    public:
      EchoTask() = default;
      EchoTask(int socket_fd);
      ~EchoTask();
      
      bool run();
      void destroy();

    private:
      int m_socket_fd = 0;
    };
  }
}
