#pragma once

#include <cstdint>

#include "icomponent.h"

namespace fml
{

  class sprite : public icomponent
  {

  private:

    int32_t _texSlot;

  public:

    sprite( int32_t slotEnum );
    virtual ~sprite() = default;

    void update( float deltaTime ) override;
    void render() override;

  };


}
