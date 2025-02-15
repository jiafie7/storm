#pragma once

#include <cstring>
#include <string>
#include <sys/resource.h>
#include <unistd.h>

#include "utility/singleton.h"
using namespace storm::utility;

namespace storm
{
  namespace utility
  {
    class System
    {
    public: 
      System() = default;
      ~System() = default;

      std::string getRootPath();

    private:
      std::string m_root_path;
    };
  }
}
