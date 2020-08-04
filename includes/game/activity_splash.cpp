#include "activity_splash.h"



activity_splash::activity_splash() {
  _fade = new fml::interpolator_linear( 5.0, 1.0 );
}

void activity_splash::load( fml::activity_manifest* manifest ) {
  fml::iactivity::load( manifest );
}

void activity_splash::update( float deltaTime ) {
  _fade->update( deltaTime );

}

void activity_splash::render() {

}
