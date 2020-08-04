#include "camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace fml
{

  camera::camera( const glm::vec3& position, const glm::vec3& direction ) {

    _position = position;
    _direction = glm::normalize( direction );

    //What about parrellel directions? Does this work somehow?
    glm::vec3 up( 0.0f, 1.0f, 0.0f );
    _right = glm::normalize( glm::cross( up, direction ) );

    _up = glm::normalize( glm::cross( direction, _right ) );
  }

  void camera::setPosition( const glm::vec3& position ) {
    _position = position;
  }
  void camera::setDirection( const glm::vec3& direction ) {
    _direction = glm::normalize( direction );
  }
  void camera::setTarget( const glm::vec3& target ) {
    _direction = glm::normalize( _position - target );
  }
  void camera::setUp( const glm::vec3& up ) {
    _up = glm::normalize( up );
  }

  void camera::movePosition( const glm::vec3& distance ) {
    _position += distance;
  }
  void camera::movePosition( float distance ) {
    _position += distance * _direction;
  }

  glm::mat4 camera::getViewMat() {
    return glm::lookAt( _position, _position + _direction, _up );
  }
}
