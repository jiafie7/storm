#pragma once

#include <iostream>
#include <pthread.h>

namespace storm
{
  namespace thread
  {
    class Thread
    {
    public:
      Thread();
      virtual ~Thread();

      void start();
      void stop();

      virtual void run() = 0;

    protected:
      static void* thread_func(void* ptr);

    protected:
      pthread_t m_tid;
    };
  }
}
