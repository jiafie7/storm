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
  
  struct MsgHead msg_head;
  std::memset(&msg_head, 0, sizeof(msg_head));
  int len = client.recv((char*)&msg_head, sizeof(msg_head));

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
    // recv message head
    if (len != sizeof(msg_head))
    {
      log_error("msg head length error: %d.", len);
      m_closed = true;
      return;
    }
    log_debug("msg head: cmd = %d, len = %d.", msg_head.cmd, msg_head.len);

    if (msg_head.len > (uint16_t)recv_buf_size)
    {
      log_error("msg body too large: len = %d.", msg_head.len);
      m_closed = true;
      return;
    }

    // recv message body
    char buf[recv_buf_size] = {0};
    len = client.recv(buf, msg_head.len);
    if (len != msg_head.len)
    {
      log_error("msg body length error: %d.", len);
      m_closed = true;
      return;
    }
    log_debug("msg body: conn = %d, len = %d, data = %s.", m_socket_fd, len, buf);

    int work_id = (int)msg_head.cmd;

    std::string output;
    // run workflow
    auto workflow = Singleton<Workflow>::getInstance();
    workflow->run(work_id, buf, output);

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
