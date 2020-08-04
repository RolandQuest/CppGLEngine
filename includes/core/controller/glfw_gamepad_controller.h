#pragma once

#include "GLFW/glfw3.h"

#include "icontroller.h"

namespace fml
{
  class glfw_gamepad_controller : public icontroller
  {

  private:

    unsigned char _gamepadId;

    GLFWgamepadstate _gamepadState;

  public:

    glfw_gamepad_controller( unsigned short id );

    ButtonState getButtonState( Button button ) override;

    float getAxisState( Axis axis ) override;

    void pollEvents() override;

  };


}

