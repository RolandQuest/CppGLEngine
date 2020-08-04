#include "glfw_gamepad_controller.h"



namespace fml
{

  glfw_gamepad_controller::glfw_gamepad_controller( unsigned short id ) {
    _gamepadId = id;
  }

  ButtonState glfw_gamepad_controller::getButtonState( Button button ) {
    return gamepadState.buttons[(int) button];
  }

  float glfw_gamepad_controller::getAxisState( Axis axis ) {
    return _gamepadState.axes[(int) axis];
  }

  void glfw_gamepad_controller::pollEvents() {

    if ( !glfwJoystickPresent( _gamepadId ) ) {
      glfwGetGamepadState( _gamepadId, &_gamepadState );
    }
  }

}
