#pragma once

#include "glm/glm.hpp"

namespace fml
{

  class transform
  {

  private:

    glm::vec3 _rotationZ = glm::vec3( 0.0f, 0.0f, 1.0f );
    glm::vec3 _position = glm::vec3( 0.0f, 0.0f, 0.0f );
    glm::vec3 _scale = glm::vec3( 1.0f, 1.0f, 1.0f );
    float _rotation = 0.0f;

  public:

    transform() = default;
    virtual ~transform() = default;

    glm::mat4 getModel();

    void setPosition( const glm::vec3& position_vec );
    void setScale( const glm::vec3& scale_vec );
    void setRotation( float radians );

    void translate( const glm::vec3& translation_vec );
    void scale( const glm::vec3& scalar_vec );
    void scale( float scalar );
    void rotate( float radians );

    void setLayer( float layer );

  };

}

