#pragma once

#include <cstring>
#include <dirent.h> 
#include <string>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utility/singleton.h"
using namespace storm::utility;

namespace storm
{
  namespace utility
  {
    class System
    {
      SINGLETON(System);
    public: 
      void init();
      std::string getRootPath();

    private:
      void coreDump();

    private:
      std::string m_root_path;
    };
  }
}
