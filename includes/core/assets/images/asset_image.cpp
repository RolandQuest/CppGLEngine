#include "asset_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h""

#include "log/log.h"
#include "gl/gl_tex_slot_manager.h"

namespace fml
{

  asset_image::asset_image( const std::string& name, const std::string& filePath, bool flipImage ) : iasset(name) {

    stbi_set_flip_vertically_on_load( flipImage );
    unsigned char* data = stbi_load( filePath.c_str(), &_width, &_height, &_numChannels, 0 );

    if ( data == nullptr ) {
      return;
    }

    if ( _numChannels == 3 ) {
      _format = GL_RGB;
    }
    else {
      _format = GL_RGBA;
    }

    stbi_set_flip_vertically_on_load( false );

    if ( gl_tex_slot_manager::requestSlot( GL_TEXTURE_2D, _texHandle, _texSlot ) ) {
      glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, _format, GL_UNSIGNED_BYTE, data );
      glGenerateMipmap( GL_TEXTURE_2D );
      _isLoaded = true;
    }
    else {
      Log( "Unable to find available texture slot in OpenGL:" );
      Log( '\t', "Name: ", name );
      Log( '\t', "Path: ", filePath );
    }

    stbi_image_free( data );
  }

  asset_image::~asset_image() {
    if ( _isLoaded ) {
      gl_tex_slot_manager::freeSlot( _texHandle );
    }
  }

  int32_t asset_image::width() const {
    return _width;
  }

  int32_t asset_image::height() const {
    return _height;
  }

  int32_t asset_image::channels() const {
    return _numChannels;
  }

  GLenum asset_image::format() const {
    return _format;
  }

  bool asset_image::isLoaded() const {
    return _isLoaded;
  }

}
