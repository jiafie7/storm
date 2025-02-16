#pragma once

#include <vector>
#include "engine/plugin_helper.h"

namespace storm
{
  namespace engine
  {
    class Work
    {
    public:
      Work();
      ~Work();

      void setId(int id); 
      int getId() const;
      
      void setSwitch(bool flag);
      bool getSwitch() const;

      // add a plugin to work
      void append(Plugin* plugin);

      // run plugins in work sequentially
      bool run();
        
    private:
      int m_id;
      bool m_switch;
      std::vector<Plugin*> m_plugins; // loaded plugins in work
    };
  }
}

