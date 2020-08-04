#pragma once

#include "glad/glad.h"

namespace fml
{

  namespace gl_tex_slot_manager
  {

    GLint slotCount();

    bool requestSlot( GLenum target, GLuint& handle, GLenum& slot );

    void freeSlot( GLuint handle );

  };

}

