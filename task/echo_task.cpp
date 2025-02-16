#include "task/echo_task.h"
using namespace storm::task;

#include "socket/socket_handler.h"
using namespace storm::socket;

EchoTask::EchoTask(int socket_fd)
  : m_socket_fd(socket_fd)
{}

EchoTask::~EchoTask()
{
}

void EchoTask::run()
{
  log_debug("echo task run.");

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
    log_debug("socket closed by peer: conn = %d.", m_socket_fd);
    m_closed = true;
    return;
  }
  else
  {
    log_debug("recv: conn = %d, msg = %s.", m_socket_fd, buf);

    std::string msg = "hi, I am server!";
    client.send(msg.c_str(), msg.size());
  }
}

void EchoTask::destroy()
{
  log_debug("echo task destroy.");
  if (m_closed)
    ::close(m_socket_fd);
  else
    Singleton<SocketHandler>::getInstance()->attach(m_socket_fd);
  delete this;
}

