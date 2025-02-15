#include "socket/socket_handler.h"

using namespace storm::socket;

int main()
{
  Singleton<LogSystem>::getInstance()->open("./../server.log");

  SocketHandler* handler = Singleton<SocketHandler>::getInstance();

  handler->listen("127.0.0.1", 7777);

  handler->handle(1024, -1);
  
  return 0;
}
