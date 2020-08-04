#pragma once

#include "glm/glm.hpp"

namespace fml
{

  class camera
  {

  private:

    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _up;
    glm::vec3 _right;

  public:

    camera() = default;
    camera( const glm::vec3& position, const glm::vec3& direction );
    virtual ~camera() = default;

    glm::mat4 getViewMat();

    void setPosition( const glm::vec3& position );
    void setDirection( const glm::vec3& direction );
    void setTarget( const glm::vec3& target );
    void setUp( const glm::vec3& up );

    void movePosition( const glm::vec3& distance );
    void movePosition( float distance );



    //zoom in/out


  };


}
