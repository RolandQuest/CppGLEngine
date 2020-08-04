#include "sprite.h"

#include "gl/gl_shader_program.h"

namespace fml
{

  sprite::sprite( int32_t slotEnum ) {
    _texSlot = slotEnum;
  }

  void sprite::update( float deltaTime ) {

  }

  void sprite::render() {
    gl_shader_program::setInt( "tex", _texSlot );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
  }

}
