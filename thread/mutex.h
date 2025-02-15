#pragma once

#include <pthread.h>

namespace storm
{
  namespace thread
  {
    class Mutex
    {
      friend class Cond;
    public:
      Mutex();
      ~Mutex();

      void lock();
      bool tryLock();
      void unlock();

    private:
      pthread_mutex_t m_mutex;
    };
  }
}
