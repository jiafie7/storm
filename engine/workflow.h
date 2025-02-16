#pragma once 

#include <map>
#include <string>

#include "utility/singleton.h"
using namespace storm::utility;

#include "xml/xml.h"
using namespace storm::xml;

#include "engine/work.h"

namespace storm
{
  namespace engine
  {
    class Workflow
    {
      SINGLETON(Workflow);
    public:
      // load works in workflow
      bool load(const std::string& config);
      // run work id
      bool run(int id, const std::string& input, std::string& output);

    private:
      // load plugins in work
      bool load_plugin(Work* work, Xml& elem);

    private:
      // mapping id and work
      std::map<int, Work*> m_works;
    };
  }
}

