#include "game_object.h"

namespace fml
{

  game_object::game_object() {

  }

  void game_object::addChild( game_object* child ) {
    _children.push_back( child );
  }

  void game_object::addComponent( icomponent* component ) {
    _components.push_back( component );
  }

  void game_object::changeLayer( float layer ) {
    _transform.setLayer(layer);
  }

  void game_object::update( float deltaTime ) {
    for ( auto& comp : _components ) {
      comp->update( deltaTime );
    }
    for ( auto& child : _children ) {
      child->update( deltaTime );
    }
  }

  void game_object::render() {
    for ( auto& comp : _components ) {
      comp->render();
    }
    for ( auto& child : _children ) {
      child->render();
    }
  }

}