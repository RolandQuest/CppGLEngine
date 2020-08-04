#include "gl_shader_program.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include "glm/gtc/type_ptr.hpp"

namespace fml
{
  namespace gl_shader_program
  {
    namespace {

      bool _isInitialized = false;
      std::map<GLint, program_uniform_attribute> _Uniforms;
      std::map<GLint, program_uniform_attribute> _Attributes;
      GLuint _ID, VAO, VBO, EBO;

      void CreateArrayObject() {
        /*
        GLfloat vertices_texture[] = {
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f
        };
        */
        GLfloat vertices_texture[] = {
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
        };
        

        GLint indices_square[] = {
          0, 1, 3,
          1, 2, 3
        };

        glGenBuffers( 1, &VBO );
        glGenBuffers( 1, &EBO );
        glGenVertexArrays( 1, &VAO );

        glBindVertexArray( VAO );

        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices_texture ), vertices_texture, GL_STATIC_DRAW );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices_square ), indices_square, GL_STATIC_DRAW );

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (void*) 0 );
        glEnableVertexAttribArray( 0 );

        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (void*) ( 3 * sizeof( GLfloat ) ) );
        glEnableVertexAttribArray( 1 );

      }

      GLint CreateShader( GLenum type, const char* path ) {

        std::string codeString;
        std::ifstream stream( path );
        std::stringstream ss;

        ss << stream.rdbuf();
        codeString = ss.str();
        stream.close();

        const char* code = codeString.c_str();
        GLint success, shader;
        char infoLog[512];

        shader = glCreateShader( type );
        glShaderSource( shader, 1, &code, 0 );
        glCompileShader( shader );

        glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
        if ( !success ) {
          glGetShaderInfoLog( shader, 512, nullptr, infoLog );
          std::cerr << "Shader Compilation Error: " << infoLog << '\n';
        }

        return shader;
      }

      void CreateProgram( GLint vShader, GLint fShader ) {

        _ID = glCreateProgram();
        glAttachShader( _ID, vShader );
        glAttachShader( _ID, fShader );
        glLinkProgram( _ID );

        GLint success;
        char infoLog[512];

        glGetProgramiv( _ID, GL_LINK_STATUS, &success );
        if ( !success ) {
          glGetProgramInfoLog( _ID, 512, nullptr, infoLog );
          std::cerr << "Program Linking Error: " << infoLog << '\n';
        }

      }

      void DetectAttributes() {

        GLint attribsCount;
        glGetProgramiv( _ID, GL_ACTIVE_ATTRIBUTES, &attribsCount );

        static const GLsizei bufSize = 32;
        GLsizei biggestBufSize;
        glGetProgramiv( _ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &biggestBufSize );

        if ( biggestBufSize > bufSize ) {
          std::cerr << "gl_shader_program: Attribute name longer than buffer size of " << bufSize << '.' << '\n';
          std::cerr << "No detection of attributes done." << '\n';
        }

        for ( GLuint i = 0; i < (GLuint) attribsCount; i++ ) {

          _Attributes[i] = program_uniform_attribute();

          GLsizei length;
          GLchar name[bufSize];

          glGetActiveAttrib( _ID, i, bufSize, &length, &_Attributes[i].size, &_Attributes[i].type, name );
          _Attributes[i].name = name;
        }
      }

      void DetectUniforms() {

        GLint attribsCount;
        glGetProgramiv( _ID, GL_ACTIVE_UNIFORMS, &attribsCount );

        static const GLsizei bufSize = 32;
        GLsizei biggestBufSize;
        glGetProgramiv( _ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &biggestBufSize );

        if ( biggestBufSize > bufSize ) {
          std::cerr << "gl_shader_program: Uniform name longer than buffer size of " << bufSize << '.' << '\n';
          std::cerr << "No detection of uniforms done." << '\n';
        }

        for ( GLuint i = 0; i < (GLuint) attribsCount; i++ ) {

          _Uniforms[i] = program_uniform_attribute();

          GLsizei length;
          GLchar name[bufSize];

          glGetActiveUniform( _ID, i, bufSize, &length, &_Uniforms[i].size, &_Uniforms[i].type, name );
          _Uniforms[i].name = name;
        }
      }

    }

    void initialize( const char* vertexPath, const char* fragmentPath ) {

      if ( _isInitialized ) {
        return;
      }

      GLint vShader = CreateShader( GL_VERTEX_SHADER, vertexPath );
      GLint fShader = CreateShader( GL_FRAGMENT_SHADER, fragmentPath );

      CreateProgram( vShader, fShader );
      CreateArrayObject();

      glDeleteShader( vShader );
      glDeleteShader( fShader );

      DetectAttributes();
      DetectUniforms();
      glUseProgram( _ID );
      _isInitialized = true;
    }

    void setBool( GLint location, bool value ) {
      glUniform1i( location, (GLint) value );
    }
    void setBool( const std::string& name, bool value ) {
      glUniform1i( glGetUniformLocation( _ID, name.c_str() ), (GLint) value );
    }

    void setInt( GLint location, GLint value ) {
      glUniform1i( location, value );
    }
    void setInt( const std::string& name, GLint value ) {
      glUniform1i( glGetUniformLocation( _ID, name.c_str() ), value );
    }

    void setFloat( GLint location, GLfloat value ) {
      glUniform1f( location, value );
    }
    void setFloat( const std::string& name, GLfloat value ) {
      glUniform1f( glGetUniformLocation( _ID, name.c_str() ), value );
    }

    void setVec4( GLint location, const glm::vec4& value ) {
      glUniform4f( location, value[0], value[1], value[2], value[3] );
    }
    void setVec4( const std::string& name, const glm::vec4& value ) {
      glUniform4f( glGetUniformLocation( _ID, name.c_str() ), value[0], value[1], value[2], value[3] );
    }

    void setMat4( GLint location, const glm::mat4& value ) {
      glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( value ) );
    }
    void setMat4( const std::string& name, const glm::mat4& value ) {
      glUniformMatrix4fv( glGetUniformLocation( _ID, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
    }

    GLuint id() {
      return _ID;
    }

    bool getAttribute( GLint location, program_uniform_attribute& attrib ) {

      if ( _Attributes.count( location ) == 0 ) {
        return false;
      }
      attrib = _Attributes[location];
      return true;
    }
    bool getAttribute( const std::string& name, program_uniform_attribute& attrib ) {

      for ( auto& attribute : _Attributes ) {
        if ( attribute.second.name == name ) {
          attrib = attribute.second;
          return true;
        }
      }
      return false;
    }

    bool getUniform( GLint location, program_uniform_attribute& uni ) {

      if ( _Uniforms.count( location ) == 0 ) {
        return false;
      }
      uni = _Uniforms[location];
      return true;
    }
    bool getUniform( const std::string& name, program_uniform_attribute& uni ) {

      for ( auto& unif : _Uniforms ) {
        if ( unif.second.name == name ) {
          uni = unif.second;
          return true;
        }
      }
      return false;
    }

    size_t attributeSize() {
      return _Attributes.size();
    }
    size_t uniformSize() {
      return _Uniforms.size();
    }

  }

}