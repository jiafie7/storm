#include "plugin/echo_plugin.h"
using namespace storm::plugin;

#include "utility/log_system.h"
#include "utility/system.h"
using namespace storm::utility;

EchoPlugin::EchoPlugin()
  :  Plugin()
{
  System* sys = Singleton<System>::getInstance();
  const std::string& root_path = sys->getRootPath();

  LogSystem* log_system = Singleton<LogSystem>::getInstance();
  log_system->open(root_path + "/log/echo_plugin.log");
  log_system->setConsole(false);
}

EchoPlugin::~EchoPlugin()
{
}

bool EchoPlugin::run(Context& ctx)
{
  std::string input = ctx.get<std::string>("input");

  log_info("echo plugin run!");
  log_info("context input: %s", input.c_str());

  ctx.set("output", "echo plugin output: " + input);
  return true;
}
