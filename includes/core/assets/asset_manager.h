#pragma once

#include <map>
#include <string>

#include "iasset.h"
#include "asset_loaders.h"

namespace fml
{

  struct asset_info {
    std::string name;
    std::string type;
    std::string path;
  };

  namespace asset_manager
  {

    bool isAssetLoaded( const std::string& assetName );

    bool loadAsset( const std::string& type, const std::string& assetName, const std::string& assetPath );

    void registerLoader( const std::string& type, iasset_loader* loader );

    void unLoadAsset( const std::string& assetName );

    iasset* getAsset( const std::string& assetName );

    size_t assetCount();

  };


}
