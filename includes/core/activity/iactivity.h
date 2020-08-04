#pragma once

#include <vector>
#include <map>

#include "manifests/activity_manifest.h"
#include "activity/game_object.h"

namespace fml
{

  class iactivity
  {

  private:

    std::vector<game_object*> _GameObjects;

  public:

    iactivity() = default;
    iactivity( activity_manifest* manifest );
    virtual ~iactivity();

    virtual void load( activity_manifest* manifest );

    virtual void update( float deltaTime );

    virtual void render();

  };


}
