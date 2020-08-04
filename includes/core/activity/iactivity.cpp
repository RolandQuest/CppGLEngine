#include "iactivity.h"

#include "assets/asset_manager.h"

namespace fml
{

  iactivity::iactivity( activity_manifest* manifest ) {
    load( manifest );
  }

  iactivity::~iactivity() {
    
  }

  void iactivity::load( activity_manifest* manifest ) {

    for ( auto& entry : manifest->getToStartAssetPaths() ) {
      if ( !asset_manager::isAssetLoaded( entry->name ) ) {
        asset_manager::loadAsset( entry->type, entry->name, entry->path );
      }
    }
    for ( auto& entry : manifest->getAdditionalAssetPaths() ) {
      if ( !asset_manager::isAssetLoaded( entry->name ) ) {
        asset_manager::loadAsset( entry->type, entry->name, entry->path );
      }
    }
  }

  void iactivity::update( float deltaTime ) {
    for ( auto& obj : _GameObjects ) {
      obj->update( deltaTime );
    }
  }

  void iactivity::render() {
    for ( auto& obj : _GameObjects ) {
      obj->render();
    }
  }

}