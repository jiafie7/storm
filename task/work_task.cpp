#include "task/work_task.h"
using namespace storm::task;

#include "socket/socket_handler.h"
using namespace storm::socket;

#include "engine/workflow.h"
using namespace storm::engine;

WorkTask::WorkTask(int socket_fd)
  : Task()
  , m_socket_fd(socket_fd)
{
}

WorkTask::~WorkTask()
{
}

void WorkTask::run()
{
  log_debug("work task run.");

  Socket client(m_socket_fd);

  char buf[1024] = {0};
  int len = client.recv(buf, sizeof(buf));

  if (len < 0)
  {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
    {
      log_debug("socket recv would block: conn = %d, errno = %d, errmsg = %s.", m_socket_fd, errno, strerror(errno));
      return;
    }
    else if (errno == EINTR)
    {
      log_debug("socket recv interrupted: conn = %d, errno = %d, errmsg = %s.", m_socket_fd, errno, strerror(errno));
      return;
    }
    else
    {
      log_error("socket connection abort: conn = %d, errno = %d, errmsg = %s.", m_socket_fd, errno, strerror(errno));
      m_closed = true;
      return;
    }
  }
  else if (len == 0)
  {
    log_error("socket closed by peer: conn = %d, errno = %d, errmsg = %s.", m_socket_fd, errno, strerror(errno));
    m_closed = true;
    return;
  }
  else
  {
    log_debug("recv: conn = %d, msg = %s.", m_socket_fd, buf);

    std::string output;
    // run workflow
    auto workflow = Singleton<Workflow>::getInstance();
    workflow->run(1, buf, output);

    client.send(output.c_str(), output.size());
    
    return;
  }
}

void WorkTask::destroy()
{
  log_debug("work task destroy.");
  if (m_closed)
    ::close(m_socket_fd);
  else
    Singleton<SocketHandler>::getInstance()->attach(m_socket_fd);
  delete this;
}
