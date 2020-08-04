#include "interpolator_linear.h"

namespace fml
{

  interpolator_linear::interpolator_linear( float time, float distance ) : iinterpolator( time ) {
    _distance = distance;
  }

  float interpolator_linear::getValue() {
    return _sumTime * _distance / _totalTime;
  }


}