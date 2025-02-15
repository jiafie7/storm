#include "thread/thread_pool.h"

using namespace storm::thread;

void ThreadPool::create(int threads)
{
  AutoLock lock(&m_mutex);
  for (int i = 0; i < threads; ++ i)
  {
    WorkerThread* thread = new WorkerThread();
    thread->start();
    m_pool.push_back(thread);
  }
  log_debug("thread pool create worker threads: %d", threads);
  m_threads = threads;
}

bool ThreadPool::empty()
{
  AutoLock lock(&m_mutex);
  return m_pool.empty();
}

void ThreadPool::assign(Task* task)
{
  WorkerThread* thread = get();
  thread->assign(task);
}

WorkerThread* ThreadPool::get()
{
  AutoLock lock(&m_mutex);

  while (m_pool.empty())
    m_cond.wait(&m_mutex);

  WorkerThread* thread = m_pool.front();
  m_pool.pop_front();

  return thread;
}

void ThreadPool::push(WorkerThread* thread)
{
  AutoLock lock(&m_mutex);

  m_pool.push_back(thread);

  m_cond.signal();
}
