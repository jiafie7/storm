#include "socket/socket_handler.h"
using namespace storm::socket;

#include "thread/task_dispatcher.h"
using namespace storm::thread;

int main()
{
  Singleton<LogSystem>::getInstance()->open("./../server.log");

  TaskDispatcher* dispatcher = Singleton<TaskDispatcher>::getInstance();
  dispatcher->init(16);

  SocketHandler* handler = Singleton<SocketHandler>::getInstance();

  handler->listen("127.0.0.1", 7777);

  handler->handle(1024, -1);
  
  return 0;
}
