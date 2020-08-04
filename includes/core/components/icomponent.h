#pragma once

namespace fml
{

  class icomponent
  {

  private:

  public:

    virtual void update( float deltaTime ) = 0;

    virtual void render() = 0;

  };


}
