#include "transform.h"

#include "glm/gtc/matrix_transform.hpp"

namespace fml
{

  glm::mat4 transform::getModel() {
    glm::mat4 ret( 1.0f );
    ret = glm::translate( ret, _position );
    ret = glm::scale( ret, _scale );
    ret = glm::rotate( ret, _rotation, _rotationZ );
    return ret;
  }

  void transform::setPosition( const glm::vec3& position_vec ) {
    _position = position_vec;
  }
  void transform::setScale( const glm::vec3& scale_vec ) {
    _scale = scale_vec;
  }
  void transform::setRotation( float radians ) {
    _rotation = radians;
  }

  void transform::translate( const glm::vec3& translation_vec ) {
    _position += translation_vec;
  }

  void transform::scale( const glm::vec3& scalar_vec ) {
    _scale *= scalar_vec;
  }

  void transform::scale( float scalar ) {
    _scale *= scalar;
  }

  void transform::rotate( float radians ) {
    _rotation += radians;
  }

  void transform::setLayer( float layer ) {
    _position.z = layer;
  }

}
