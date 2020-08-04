#include "iinterpolator.h"

namespace fml
{

  iinterpolator::iinterpolator( float time ) {
    _totalTime = time;
  }

  bool iinterpolator::isComplete() {
    return _sumTime >= _totalTime;
  }

  void iinterpolator::reset() {
    _sumTime = 0.0;
  }

  void iinterpolator::update( float deltaTime ) {
    _sumTime += deltaTime;
  }


}