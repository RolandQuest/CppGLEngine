#pragma once

#include <string>
#include <vector>

#include "math/transform.h"
#include "components/icomponent.h"

namespace fml
{

  class game_object
  {

  private:

    std::string _name;
    transform _transform;

    game_object* _parent = nullptr;
    std::vector<game_object*> _children;

    std::vector<icomponent*> _components;
    
    //std::vector<behavior*> _behaviors;
    
  public:

    game_object();

    virtual ~game_object() = default;

    void addChild( game_object* child );

    void addComponent( icomponent* component );

    void changeLayer( float layer );

    void update( float deltaTime );

    void render();

  };

}