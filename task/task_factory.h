#pragma once

#include "task/echo_task.h"
#include "task/work_task.h"
using namespace storm::task;

namespace storm
{
  namespace task
  {
    class TaskFactory
    {
    public:
      static Task* create(int socket_fd)
      {
        return new WorkTask(socket_fd);
      }
    };
  }
}
