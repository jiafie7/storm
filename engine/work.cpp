#include "engine/work.h"
using namespace storm::engine;

Work::Work()
  : m_id(0)
  , m_switch(false)
{}

Work::~Work()
{
  for (auto it = m_plugins.begin(); it != m_plugins.end(); ++ it)
  {
    const std::string& plugin = (*it)->getName();
    destroy_plugin func = (destroy_plugin)Singleton<PluginHelper>::getInstance()->symbol(plugin, "destroy");
    func(*it);
  }
}
     
void Work::setId(int id) { m_id = id; }

int Work::getId() const { return m_id; }      

void Work::setSwitch(bool flag) { m_switch = flag; }

bool Work::getSwitch() const { return m_switch; }

void Work::append(Plugin* plugin)
{
  m_plugins.push_back(plugin);
}
      
bool Work::run(Context& ctx)
{
  for (auto it = m_plugins.begin(); it != m_plugins.end(); ++ it)
  {
    if ((*it)->getSwitch())
      if (!(*it)->run(ctx))
        break;
  }

  return true; 
}

