#include "gl_tex_slot_manager.h"

#include <map>

namespace fml
{
  namespace gl_tex_slot_manager
  {

    namespace {

      std::map<GLenum, GLuint> _usedSlots;

      bool _findOpenSlot( GLenum& slot ) {

        for ( GLint i = 0, stop = slotCount(); i < stop; i++ ) {
          if ( _usedSlots.count( GL_TEXTURE0 + i ) == 0 ) {
            slot = GL_TEXTURE0 + i;
            return true;
          }
        }
        return false;
      }

    }

    GLint slotCount() {
      GLint ret;
      glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &ret );
      return ret;
    }

    bool requestSlot( GLenum target, GLuint& handle, GLenum& slot ) {

      if ( !_findOpenSlot( slot ) ) {
        return false;
      }

      glGenTextures( 1, &handle );
      glActiveTexture( slot );
      glBindTexture( target, handle );
      glTexParameteri( target, GL_TEXTURE_WRAP_S, GL_REPEAT );
      glTexParameteri( target, GL_TEXTURE_WRAP_T, GL_REPEAT );

      //glTexParameteri( target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
      //glTexParameteri( target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );

      //float borderColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
      //glTexParameterfv( target, GL_TEXTURE_BORDER_COLOR, borderColor );

      glTexParameteri( target, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
      glTexParameteri( target, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

      _usedSlots[slot] = handle;
      return true;
    }

    void freeSlot( GLuint handle ) {
      
      for ( auto& entry : _usedSlots ) {
        if ( entry.second == handle ) {
          _usedSlots.erase( entry.first );
          break;
        }
      }
      glDeleteTextures( 1, &handle );
    }


  }
}


