#include "frame/server.h"
using namespace storm::frame;

#include "engine/workflow.h"
#include "engine/context.h"
using namespace storm::engine;

int main()
{
  Singleton<Server>::getInstance()->start();
 
  return 0;
}
