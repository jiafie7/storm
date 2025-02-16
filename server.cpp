#include "frame/server.h"
using namespace storm::frame;

#include "engine/context.h"
using namespace storm::engine;

int main()
{
  // Singleton<Server>::getInstance()->start();

  Context ctx;
  ctx.set("name", "jack");
  ctx.set("age", 23);

  std::string name = ctx.get<std::string>("name");
  int age = ctx.get<int>("age");

  std::cout << "name = " << name << ", age = " << age << '\n';

  return 0;
}
