#include "thread/task_dispatcher.h"

using namespace storm::thread;

void TaskDispatcher::init(int threads)
{
  Singleton<ThreadPool>::getInstance()->create(threads);
  start();
}

bool TaskDispatcher::empty()
{
  AutoLock lock(&m_mutex);

  return m_tasks.empty();
}

void TaskDispatcher::push(Task* task)
{
  log_debug("task dispatcher get task: %x", task);
  AutoLock lock(&m_mutex);

  m_tasks.push_back(task);

  m_cond.signal();
}

void TaskDispatcher::dispatch(Task* task)
{
  ThreadPool* pool = Singleton<ThreadPool>::getInstance();

  if (pool->empty())
  {
    AutoLock lock(&m_mutex);
    m_tasks.push_back(task);
    log_warn("all worker threads are busy!");
  }
  else
    pool->assign(task);
}

void TaskDispatcher::run()
{
  sigset_t mask;
  if (0 != sigfillset(&mask))
  {
    log_error("task dispatcher sigfillset error!");
    return;
  }
  if (0 != pthread_sigmask(SIG_SETMASK, &mask, nullptr))
  {
    log_error("task dispatcher pthread_sigmask error!");
    return;
  }

  while (true)
  {
    AutoLock lock(&m_mutex);

    if (m_tasks.empty())
      m_cond.wait(&m_mutex);
  
    Task* task = m_tasks.front();
    m_tasks.pop_front();

    dispatch(task);
  }
}
