#include "asset_loaders.h"

#include "images/asset_image.h"

namespace fml
{

  iasset* image_asset_loader::load( const std::string& name, const std::string& assetPath ) {
    return new asset_image( name, assetPath, true );
  }

}