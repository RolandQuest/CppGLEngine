#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace fml
{
  namespace gl_shader_program
  {

    struct program_uniform_attribute {
      GLint size;
      GLenum type;
      std::string name;
    };

    void initialize( const char* vertexPath, const char* fragmentPath );

    void setBool( GLint location, bool value );
    void setBool( const std::string& name, bool value );

    void setInt( GLint location, GLint value );
    void setInt( const std::string& name, GLint value );

    void setFloat( GLint location, GLfloat value );
    void setFloat( const std::string& name, GLfloat value );

    void setVec4( GLint location, const glm::vec4& value );
    void setVec4( const std::string& name, const glm::vec4& value );

    void setMat4( GLint location, const glm::mat4& value );
    void setMat4( const std::string& name, const glm::mat4& value );

    GLuint id();

    bool getAttribute( GLint location, program_uniform_attribute& attrib );
    bool getAttribute( const std::string& name, program_uniform_attribute& attrib );

    bool getUniform( GLint location, program_uniform_attribute& uni );
    bool getUniform( const std::string& name, program_uniform_attribute& uni );

    size_t attributeSize();
    size_t uniformSize();

  }

}

#endif