#pragma once

namespace fml
{
  namespace window
  {

    bool initialize();

    float width();

    float height();

    float aspectRatio();

    void shutdown();

    void swapBuffers();

    bool shouldClose();

    void pollEvents();

    //bool requestGamepad(int& id);

    unsigned char getGamepadState( int button );

    float getGamepadAxisState( int axis );

  }
}