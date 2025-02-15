#include "socket/socket_handler.h"
using namespace storm::socket;

#include "thread/task_dispatcher.h"
using namespace storm::thread;

#include "utility/ini_parser.h"
using namespace storm::utility;

int main()
{
  IniParser* ini_parser = Singleton<IniParser>::getInstance();
  ini_parser->load("./../config/server.ini");
  std::string ip = ini_parser->get("server", "ip");
  int port = ini_parser->get("server", "port");
  int threads = ini_parser->get("server", "threads");
  int max_conns = ini_parser->get("server", "max_conns");
  int log_level = ini_parser->get("server", "log_level");
  int wait_time = ini_parser->get("server", "wait_time");

  LogSystem* log_system = Singleton<LogSystem>::getInstance();
  log_system->open("./../server.log");
  log_system->setLevel(log_level);
  log_system->setConsole(false);

  TaskDispatcher* dispatcher = Singleton<TaskDispatcher>::getInstance();
  dispatcher->init(threads);

  SocketHandler* handler = Singleton<SocketHandler>::getInstance();

  handler->listen(ip, port);

  handler->handle(max_conns, wait_time);
  
  return 0;
}
