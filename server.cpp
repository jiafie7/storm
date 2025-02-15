#include "frame/server.h"
using namespace storm::frame;

int main()
{
  Singleton<Server>::getInstance()->start();

  return 0;
}
