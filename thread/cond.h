#pragma once

#include "thread/mutex.h"

namespace storm
{
  namespace thread
  {
    class Cond
    {
    public:
      Cond();
      ~Cond();

      void wait(Mutex* mutex);
      void signal();
      void broadcast();

    private:
      pthread_cond_t m_cond;
    };
  }
}

