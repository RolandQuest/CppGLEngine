#include "activity_manager.h"




namespace fml
{
  namespace activity_manager
  {

    namespace {

      iactivity* _currentActivity = nullptr;

    }

    iactivity* getCurrent() {
      return _currentActivity;
    }

    void setCurrent( iactivity* act ) {
      _currentActivity = act;
    }

  }
}



