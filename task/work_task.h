#pragma once

#include <cstdint> 
#include "thread/task.h"
using namespace storm::thread;

namespace storm
{
  namespace task
  {
    class WorkTask : public Task
    {
    public:
      WorkTask() = delete;
      WorkTask(int socket_fd);
      ~WorkTask();

      virtual void run();
      virtual void destroy();
        
    private:
      int m_socket_fd = 0;
      bool m_closed = false;
    };
  }
}
