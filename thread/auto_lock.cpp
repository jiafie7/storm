#include "thread/auto_lock.h"

using namespace storm::thread;

AutoLock::AutoLock(Mutex* mutex)
  : m_mutex(mutex)
{
  m_mutex->lock();
}

AutoLock::~AutoLock()
{
  m_mutex->unlock();
}

