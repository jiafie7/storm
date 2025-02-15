#pragma once

#include "socket/socket.h"
using namespace storm::socket;

#include "thread/task.h"
using namespace storm::thread;

namespace storm
{
  namespace task
  {
    class EchoTask : public Task
    {
    public:
      EchoTask() = default;
      EchoTask(int socket_fd);
      ~EchoTask();
      
      virtual void run();
      virtual void destroy();

    private:
      int m_socket_fd = 0;
      bool m_closed = false;
    };
  }
}
