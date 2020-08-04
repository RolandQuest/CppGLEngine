#include "window_wrapper.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "activity/activity_manager.h"
#include "log/log.h"

namespace fml
{
  namespace window
  {

    namespace {

      ///
      /// Window
      ///

      GLFWwindow* glfw_window = nullptr;

      int _width = 800.0f;
      int _height = 600.0f;
      float _aspectRatio = (float) _width / _height;

      ///
      /// Gamepad
      ///

      GLFWgamepadstate gamepadState;

      int gamepadRegistered = -1;

      void setGamepads() {

        //Only finds the first gamepad registered on load. Not dynamic.
        for ( int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; i++ ) {

          if ( glfwJoystickPresent( i ) ) {
            Log( "Joystick found! (", glfwGetGamepadName( i ), ")" );
            gamepadRegistered = i;
            break;
          }
        }
      }

      ///
      /// Callbacks
      ///

      void framebuff_size_callback( GLFWwindow* window, int width, int height ) {
        _width = width;
        _height = height;
        _aspectRatio = (float) width / height;
        glViewport( 0, 0, width, height );
        Log( "Viewport Changed: width(", width, ") height(", height, ") aspect-ratio(", _aspectRatio, ")" );
      }

      void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {

        if ( key == GLFW_KEY_D ) {
          //activity_manager::getCurrent()->buttonPressed( controller::Button::kRight, ( controller::ButtonAction) action );
        }
        if ( key == GLFW_KEY_A ) {
          //activity_manager::getCurrent()->buttonPressed( controller::Button::kLeft, ( controller::ButtonAction ) action );
        }
        if ( key == GLFW_KEY_W ) {
          //activity_manager::getCurrent()->buttonPressed( controller::Button::kUp, ( controller::ButtonAction ) action );
        }
        if ( key == GLFW_KEY_S ) {
          //activity_manager::getCurrent()->buttonPressed( controller::Button::kDown, ( controller::ButtonAction ) action );
        }
      }

    }

    bool initialize() {

      glfwInit();
      glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
      glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
      glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

      glfw_window = glfwCreateWindow( 800, 600, "LearnOpenGL", nullptr, nullptr );

      if ( glfw_window == nullptr ) {
        Log( "Failed to create GLFW window" );
        glfwTerminate();
        return false;
      }

      glfwMakeContextCurrent( glfw_window );
      glfwSetFramebufferSizeCallback( glfw_window, framebuff_size_callback );

      if ( !gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress ) ) {
        Log( "Failed to initialize GLAD" );
        return false;
      }

      setGamepads();
      glfwSetKeyCallback( glfw_window, key_callback );

      return true;
    }

    float width() {
      return _width;
    }

    float height() {
      return _height;
    }

    float aspectRatio() {
      return _aspectRatio;
    }

    void shutdown() {
      glfwTerminate();
    }

    void swapBuffers() {
      glfwSwapBuffers( glfw_window );
    }

    bool shouldClose() {
      return glfwWindowShouldClose( glfw_window );
    }

    void pollEvents() {

      glfwPollEvents();

      //Rip out after moving to controller class.
      if ( gamepadRegistered != -1 ) {
        glfwGetGamepadState( gamepadRegistered, &gamepadState );
      }
      
    }

    
    unsigned char getGamepadState( int button ) {
      return gamepadState.buttons[button];
    }

    float getGamepadAxisState( int axis ) {
      return gamepadState.axes[axis];
    }
    
  }
}



