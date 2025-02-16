#pragma once

#include "engine/plugin.h"
using namespace storm::engine;

namespace storm
{
  namespace plugin
  {
    class EchoPlugin : public Plugin 
    {
    public:
      EchoPlugin();
      virtual ~EchoPlugin();

      virtual bool run();
    };

    DEFINE_PLUGIN(EchoPlugin)
  }
}
