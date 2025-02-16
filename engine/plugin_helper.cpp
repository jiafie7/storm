#include "engine/plugin_helper.h"
using namespace storm::engine;

bool PluginHelper::load(const std::string& plugin)
{
  if (plugin.empty())
  {
    log_error("load plugin error: plugin is empty.");
    return false; 
  }
  if (m_plugins.find(plugin) != m_plugins.end())
    return true;
  
  // get plugin(so file) path
  System* sys = Singleton<System>::getInstance();
  std::string filename = sys->getRootPath() + "/plugin/" + plugin;

  // get symbol
  void* handle = dlopen(filename.c_str(), RTLD_GLOBAL | RTLD_LAZY);
  if (handle == nullptr)
  {
    log_error("load plugin error: %s", dlerror());
    return false;
  }

  m_plugins[plugin] = handle;
  return true;
}

void PluginHelper::unload(const std::string& plugin)
{
  if (plugin.empty())
  {
    log_error("unload plugin error: plugin is empty.");
    return;
  }

  auto it = m_plugins.find(plugin);
  if (it == m_plugins.end())
  {
    log_error("unload plugin error: plugin not found.");
    return;
  }

  // close symbol
  dlclose(it->second);
  m_plugins.erase(it);
}

void* PluginHelper::symbol(const std::string& plugin, const std::string& symbol)
{
  auto it = m_plugins.find(plugin);
  if (it == m_plugins.end())
  {
    if (!load(plugin))
      return nullptr;

    it = m_plugins.find(plugin);
    if (it == m_plugins.end())
    {
      log_error("load plugin error: %s", plugin.c_str());
      return nullptr;
    }
  }

  // get symbol
  void* func = dlsym(it->second, symbol.c_str());
  if (func == nullptr)
  {
    log_error("undefined symbol: plugin = %s, symbol = %s", plugin.c_str(), symbol.c_str());
  }

  return func;
}

void PluginHelper::show()
{
  for (auto it = m_plugins.begin(); it != m_plugins.end(); ++ it)
    log_debug("plugin: name = %s, handle = %x", it->first.c_str(), it->second);
}


