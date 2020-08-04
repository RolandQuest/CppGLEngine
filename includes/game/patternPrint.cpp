#include "patternPrint.h"

#include <fstream>
#include <functional>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "gl/gl_shader_program.h"
#include "log/log.h"

#include "window/window_wrapper.h"
#include "log/log.h"

patternPrint::patternPrint() {

  std::ifstream stream( "configs/pattern.txt" );

  if ( !stream.is_open() ) {
    stream.close();
    return;
  }

  _pattern = new bool* [6];

  for ( int i = 0; i < 6; i++ ) {
    _pattern[i] = new bool[6];
    std::memset( _pattern[i], 0, 6 );

    for ( int j = 0; j < 6; j++ ) {
      stream >> _pattern[i][j];
    }
  }

  stream.close();

  c = fml::camera( glm::vec3( 0.0f, 0.0f, 10.0f ), glm::vec3( 0.0f, 0.0f, -1.0f ) );

  //auto test = std::bind( &left );

  //fml::controller::registerControl( fml::controller::Button::kLeft, std::bind(&this->left) );

}

patternPrint::~patternPrint() {
  delete[] _pattern;
}


void patternPrint::update( float deltaTime ) {

  HandleControls( deltaTime );

  glm::vec3 cameraPos = glm::vec3( 0.0f, 0.0f, 10.0f );
  glm::vec3 cameraTarget = glm::vec3( 0.0f, 0.0f, 0.0f );
  glm::vec3 cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
  glm::vec3 cameraDirection = glm::normalize( cameraPos - cameraTarget );

  glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );
  glm::vec3 cameraRight = glm::normalize( glm::cross( up, cameraDirection ) );
  glm::vec3 cameraUp = glm::cross( cameraDirection, cameraRight );

  glm::mat4 identity( 1.0f );

  _current += deltaTime;
  while ( _current < 0 ) {
    _current += _cycle;
  }
  while ( _current > _cycle ) {
    _current -= _cycle;
  }
  float ambience = _current / _cycle;
  fml::gl_shader_program::setVec4( "ambience", glm::vec4( ambience, ambience, ambience, 1.0 ) );

  //Projection
  glm::mat4 projection = glm::perspective( glm::radians( zoom ), (float) 800 / 600, 0.1f, 100.0f );
  //glm::mat4 projection = glm::ortho( 0.0f, 8.0f, 0.0f, 6.0f, 0.1f, 100.0f );
  fml::gl_shader_program::setMat4( "projection", projection );
  //_program->setMat4( "projection", identity );

  //View
  //glm::mat4 view = glm::lookAt( cameraPos, cameraPos + cameraFront, cameraUp );
  fml::gl_shader_program::setMat4( "view", c.getViewMat() );
  //_program->setMat4( "view", identity );

}

void patternPrint::render() {

  for ( int i = 0; i < 6; i++ ) {
    for ( int j = 0; j < 6; j++ ) {

      //model
      glm::mat4 trans = glm::mat4( 1.0f );
      trans = glm::translate( trans, glm::vec3( 2.0f * i, 2.0f * j, 0.0f ) );

      GLint transLoc = glGetUniformLocation( fml::gl_shader_program::id(), "model" );
      glUniformMatrix4fv( transLoc, 1, GL_FALSE, glm::value_ptr( trans ) );

      fml::gl_shader_program::setInt( "tex", (int) _pattern[i][j] );
      glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    }
  }

}

void patternPrint::HandleControls( float deltaTime ) {

  if ( fml::window::getGamepadState(GLFW_GAMEPAD_BUTTON_A) ) {
    _current += deltaTime;
  }
  if ( fml::window::getGamepadState( GLFW_GAMEPAD_BUTTON_B ) ) {
    _current += deltaTime;
  }
  if ( fml::window::getGamepadState( GLFW_GAMEPAD_BUTTON_B ) == GLFW_RELEASE ) {
    //_current = 0.0;
  }
}
