#include "frame/server.h"
using namespace storm::frame;

#include "engine/workflow.h"
#include "engine/context.h"
using namespace storm::engine;

int main()
{
  // Singleton<Server>::getInstance()->start();

  Workflow* workflow = Singleton<Workflow>::getInstance();
  workflow->load("./../config/workflow.xml");

  const std::string& input = "request data";
  std::string output;

  workflow->run(1, input, output);

  std::cout << output << '\n';

  return 0;
}
