#pragma once

#include <dlfcn.h>
#include <map>
#include <string>
#include "engine/plugin.h"

#include "utility/log_system.h"
#include "utility/system.h"
using namespace storm::utility;

namespace storm
{
  namespace engine
  {
    typedef Plugin* (*create_plugin)();
    typedef void (*destroy_plugin)(Plugin* plugin);
    
    class PluginHelper
    {
      SINGLETON(PluginHelper);
    public:
      // load plugin to m_plugins
      bool load(const std::string& plugin);
      // unload plugin from m_plugins
      void unload(const std::string& plugin);
      // get the symbol of plugin
      void* symbol(const std::string& plugin, const std::string& symbol);

      void show();

    private:
      std::map<std::string, void*> m_plugins;
    };
  }
}

