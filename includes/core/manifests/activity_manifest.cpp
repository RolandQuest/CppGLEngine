#include "activity_manifest.h"

namespace fml
{

  activity_manifest::activity_manifest( const std::string& name, json& config ) {

    _name = name;

    for ( auto& assetInfo : config["assets"]["toStart"] ) {
      asset_info* info = new asset_info();
      info->name = assetInfo["name"];
      info->type = assetInfo["type"];
      info->path = assetInfo["path"];
      _toStartAssetInfos.push_back( info );
    }
    for ( auto& assetInfo : config["assets"]["additional"] ) {
      asset_info* info = new asset_info();
      info->name = assetInfo["name"];
      info->type = assetInfo["type"];
      info->path = assetInfo["path"];
      _additionalAssetInfos.push_back( info );
    }
    
    _scene = config["scene"];
  }

  const std::vector<asset_info*>& activity_manifest::getToStartAssetPaths() {
    return _toStartAssetInfos;
  }

  const std::vector<asset_info*>& activity_manifest::getAdditionalAssetPaths() {
    return _additionalAssetInfos;
  }

}

