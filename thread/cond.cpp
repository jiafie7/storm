#include "thread/cond.h"

using namespace storm::thread;

Cond::Cond()
{
  pthread_condattr_t attr;
  pthread_condattr_init(&attr);
  pthread_cond_init(&m_cond, &attr);
  pthread_condattr_destroy(&attr);
}

Cond::~Cond()
{
  pthread_cond_destroy(&m_cond);
}

void Cond::wait(Mutex* mutex)
{
  pthread_cond_wait(&m_cond, &(mutex->m_mutex));
}

void Cond::signal()
{
  pthread_cond_signal(&m_cond);
}

void Cond::broadcast()
{
  pthread_cond_broadcast(&m_cond);   
}
