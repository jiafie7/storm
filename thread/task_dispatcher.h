#pragma once

#include "thread/thread_pool.h"

using namespace storm::thread;

namespace storm
{
  namespace thread
  {
    class TaskDispatcher : public Thread
    {
      SINGLETON(TaskDispatcher);
    public:
      void init(int threads);
      bool empty();

      void push(Task* task);

      void dispatch(Task* task);

      virtual void run(); 

    private:
      Mutex             m_mutex;
      Cond              m_cond;
      std::list<Task*>  m_tasks; 
    };
  }
}
