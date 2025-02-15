#pragma once

#include <signal.h>

#include "thread/cond.h"
#include "thread/mutex.h"
#include "thread/task.h"
#include "thread/thread.h"

#include "utility/log_system.h"
using namespace storm::utility;

namespace storm
{
  namespace thread
  {
    class WorkerThread : public Thread
    {
    public:
      WorkerThread();
      ~WorkerThread();

      void assign(Task* task);
      virtual void run();

      static void cleanup(void* ptr);

    private:
      Task* m_task;
      Mutex m_mutex;
      Cond  m_cond;
    };
  }
}
