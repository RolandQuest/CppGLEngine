#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

#include "glad/glad.h"
#include "assets/iasset.h"

namespace fml
{

  class asset_image : public iasset
  {

  private:

    bool _isLoaded = false;

    int32_t _width = 0;
    int32_t _height = 0;
    int32_t _numChannels = 0;
    GLenum _format = GL_RGB;

    GLenum _texSlot;
    GLuint _texHandle;

  public:

    asset_image( const std::string& name, const std::string& filePath, bool flipImage = false );
    virtual ~asset_image();

    int32_t width() const;
    int32_t height() const;
    int32_t channels() const;
    GLenum format() const;
    bool isLoaded() const;

  };

}



#endif