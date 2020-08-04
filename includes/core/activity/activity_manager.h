#pragma once

#include "iactivity.h"

namespace fml
{
  namespace activity_manager
  {

    iactivity* getCurrent();

    void setCurrent( iactivity* act );
  }
}



