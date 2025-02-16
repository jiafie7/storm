#include "frame/server.h"
using namespace storm::frame;

#include "engine/plugin_helper.h"
using namespace storm::engine;

int main()
{
  // Singleton<Server>::getInstance()->start();

  PluginHelper* helper = Singleton<PluginHelper>::getInstance();
  helper->load("echo_plugin.so");
  void *func = helper->symbol("echo_plugin.so", "create");

  helper->show();

  return 0;
}
