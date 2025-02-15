#include "utility/system.h"
using namespace storm::utility;

std::string System::getRootPath()
{
  if (!m_root_path.empty())
    return m_root_path;

  char path[1024] = {0};
  int len = ::readlink("/proc/self/exe", path, 1024);

  if (len < 0 || len >= 1024)
    return "";
  
  // remove the name of program itself
  for (int i = len; i >= 0; -- i)
    if (path[i] == '/')
    {
      path[i] = '\0';
      break;
    }
  
  // remove path name "build/"
  len = strlen(path);
  for (int i = len - 1; i >= 0; -- i)
    if (path[i] == '/')
    {
      path[i] = '\0';
      break;
    }

  return path;
}
