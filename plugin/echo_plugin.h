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

      virtual bool run(Context& ctx);
    };

    DEFINE_PLUGIN(EchoPlugin)
  }
}
