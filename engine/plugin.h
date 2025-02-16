#pragma once

#include <string>

namespace storm
{
  namespace engine
  {
    class Plugin
    {
    public:
      Plugin()
        : m_name("")
        , m_switch(false)
      {}

      virtual ~Plugin()
      {}

      void setName(const std::string& name)
      {
        m_name = name;
      }
      const std::string& getName() const
      {
        return m_name;
      }

      void setSwitch(bool flag)
      {
        m_switch = flag;
      }
      bool getSwitch() const
      {
        return m_switch;
      }

      virtual bool run() = 0;
    
    protected:
      std::string   m_name;     // plugin name
      bool          m_switch;   // plugin switch
    };

#define DEFINE_PLUGIN(className)                \
    extern "C" Plugin* create()                 \
    {                                           \
      return new (std::nothrow) className();    \
    }                                           \
                                                \
    extern "C" void destroy(Plugin* p)          \
    {                                           \
      delete p;                                 \
      p = nullptr;                              \
    }
  }
}
