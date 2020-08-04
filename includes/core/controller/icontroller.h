#pragma once

namespace fml
{

  enum class Button : int {
    kA, kB, kX, kY,
    kBumperLeft, kBumperRight,
    kSelect, kStart, kGuide,
    kLeftThumb, kRightThumb,
    kUp, kRight, kDown, kLeft,
    KAll
  };

  enum class Axis : int {
    kLeftX, kLeftY,
    kRightX, kRightY,
    kTriggerLeft, kTriggerRight,
    kAll
  };

  enum class ButtonState : int {

    kPressed,
    kReleased,
    kHeld

  };

  class icontroller
  {

  protected:

    bool _connected = true;

  public:

    virtual ButtonState getButtonState( Button button ) = 0;
    virtual float getAxisState( Axis axis ) = 0;
    virtual void pollEvents() = 0;

    bool isConnected();

  };



}