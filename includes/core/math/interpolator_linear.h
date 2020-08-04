#pragma once

#include "iinterpolator.h"

namespace fml
{

  class interpolator_linear : public iinterpolator
  {

  private:

    float _distance;

  public:

    interpolator_linear( float time, float distance );

    float getValue() override;


  };

}

