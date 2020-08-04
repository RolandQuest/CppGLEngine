
#include "window/window_wrapper.h"

#include "gl/gl_shader_program.h"

#include "assets/asset_manager.h"
#include "assets/images/asset_image.h"
#include "assets/asset_loaders.h"

#include "includes/game/patternPrint.h"

#include "manifests/app_manifest.h"
#include "manifests/activity_manifest.h"

#include "activity/activity_manager.h"

#include "activity/game_object.h"
#include "components/sprite.h"

#include "json/json_wrapper.h"
#include "log/log.h"

#include "gl/gl_tex_slot_manager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


int main() {

  ///
  /// Initiate logging stream.
  ///

#ifndef _FINALRELEASE
  //std::ofstream logStream( "Logs.txt", std::ios::app );
  //fml::log_TargetFileBuffer = logStream.rdbuf();
  fml::log_LogConsoleAndFileBuffer = false;
  //logStream << '\n' << fml::formatted_time() << '\t' << "Fresh Start!" << '\n';
#endif


  ///
  /// GLFW and GLAD setup.
  ///

  fml::window::initialize();


  ///
  /// Shader Program
  ///

  fml::gl_shader_program::initialize( "configs/basicShader.vs", "configs/basicShader.fs" );

  glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );

  int nrAttributes;
  glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &nrAttributes );
  fml::Log( glGetString( GL_VERSION ) );
  fml::Log( nrAttributes );


  ///
  /// Activities + Manifests
  ///

  json appManifest;
  if ( !fml::supp::load_json( "assets/manifests/app_manifest.json", appManifest ) ) {
    return 1;
  }

  fml::asset_manager::registerLoader( "image", new fml::image_asset_loader() );

  fml::app_manifest* mani = new fml::app_manifest( appManifest );
  fml::activity_manifest* entry = mani->getEntryActivityManifest();


  ///
  /// pattern (pseudo activity)
  ///

  patternPrint p;
  p.load( entry );
  fml::activity_manager::setCurrent( &p );


  ///
  /// Game Object w/ Sprite
  ///

  fml::game_object go[3];

  fml::sprite s1(2);
  go[0].addComponent( &s1 );
  go[0].changeLayer( -10000 );
  fml::sprite s2( 1 );
  go[1].addComponent( &s2 );
  go[1].changeLayer( -10000 );
  fml::sprite s3( 3 );
  go[2].addComponent( &s3 );
  go[2].changeLayer( -10000 );


  /// 
  /// Game loop
  ///

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  float secTime = 0.0f;
  int frameCount = 0;


  while ( !fml::window::shouldClose() ) {

    glClear( GL_COLOR_BUFFER_BIT );

    float totalTime = glfwGetTime();
    deltaTime = totalTime - lastFrame;
    lastFrame = totalTime;

    secTime += deltaTime;
    frameCount++;

    //currentActivity->update(window, deltaTime);
    //currentActivity->render();

    //p.processInput( window, deltaTime );
    p.update( deltaTime );
    //p.render();


    float ar = fml::window::aspectRatio();
    float scalar = 4.0f;
    
    //Projection
    //glm::mat4 projection = glm::perspective( glm::radians(80.0f), (float) 800 / 600, 0.1f, 100.0f );
    //glm::mat4 projection = glm::ortho( -400.0f, 400.0f, 300.0f, -300.0f );
    //glm::mat4 projection = glm::ortho( -4.0f/3.0f, 4.0f/3.0f, -1.0f, 1.0f, -10.0f, 10.0f );
    glm::mat4 projection = glm::ortho( -ar * scalar, ar * scalar, -1.0f * scalar, 1.0f * scalar );
    //glm::mat4 projection = glm::ortho( -32.0f, 32.0f, -32.0f, 32.0f, -10.0f, 10.0f );
    //glm::mat4 projection = glm::mat4( 1.0 );

    //View
    glm::mat4 view = glm::mat4( 1.0 );
    //glm::mat4 view = glm::lookAt( glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0) );


    for ( int i = 0; i < 3; i++ ) {

      //Model
      glm::mat4 model = glm::mat4( 1.0 );

      //model = glm::scale( model, glm::vec3( 0.10, 0.10, 0.10 ) );
      model = glm::translate( model, glm::vec3( (float) i, 0.0, 0.0 ) );

      fml::gl_shader_program::setMat4( "projection", projection );
      fml::gl_shader_program::setMat4( "view", view );
      fml::gl_shader_program::setMat4( "model", model );
      fml::gl_shader_program::setVec4( "ambience", glm::vec4( 1.0, 1.0, 1.0, 1.0 ) );

      go[i].update( deltaTime );
      go[i].render();
    }

    fml::window::swapBuffers();
    fml::window::pollEvents();

    if ( secTime > 1.0f ) {
      secTime -= 1.0f;
      fml::Log( "Frame Rate: ", (float) frameCount / totalTime );
    }
  }


  fml::window::shutdown();
  return 0;
}