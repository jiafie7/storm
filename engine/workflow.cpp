#include "engine/workflow.h"
using namespace storm::engine;

bool Workflow::load(const std::string& config)
{
  Xml root;
  root.load(config);
  for (Xml::iterator it = root.begin(); it != root.end(); ++ it)
  {
    int id = it->getAttribute("id");
    const std::string& flag = it->getAttribute("switch");

    Work* work = new Work();
    work->setId(id);
    if (flag == "on")
      work->setSwitch(true);
    else if (flag == "off")
      work->setSwitch(false);
    
    if (!load_plugin(work, *it))
    {
      log_error("workflow load plugin error: work id = %d.", id);
      return false;
    }
    m_works[id] = work;
  }

  log_info("load workflow success: %s", config.c_str());
  return true;
}

bool Workflow::load_plugin(Work* work, Xml& elem)
{
  for (Xml::iterator it = elem.begin(); it != elem.end(); ++ it)
  {
    if (it->getName() != "plugin")
    {
      log_error("plugin not supported: %s.", it->getName().c_str());
      return false;
    }

    const std::string& name = it->getAttribute("name");
    create_plugin func = (create_plugin)Singleton<PluginHelper>::getInstance()->symbol(name, "create");

    Plugin* plugin = func();
    plugin->setName(name);
    
    const std::string& flag = it->getAttribute("switch");
    if (flag == "on")
      plugin->setSwitch(true);
    else if (flag == "off")
      plugin->setSwitch(false);

    work->append(plugin);
  }
  return true;
}

bool Workflow::run(int id, const std::string& input, std::string& output)
{
  auto it = m_works.find(id);
  if (it == m_works.end())
  {
    log_error("work not found: work id = %d.", id);
    return false;
  }
  if (!(it->second->getSwitch()))
  {
    log_error("work switch off: work id = %d.", id);
    return false;
  }
  
  if (!it->second->run())
  {
    log_error("work run error: work id = %d.", id);
    return false;
  }

  return true;
}
