#pragma once

#include <vector>
#include <string>

#include "json/json_wrapper.h"
#include "assets/asset_manager.h"

namespace fml
{

  class activity_manifest
  {

  private:

    std::string _name;
    std::vector<asset_info*> _toStartAssetInfos;
    std::vector<asset_info*> _additionalAssetInfos;
    

  public:
    json _scene;
    activity_manifest( const std::string& name, json& config );
    virtual ~activity_manifest() = default;

    const std::vector<asset_info*>& getToStartAssetPaths();
    const std::vector<asset_info*>& getAdditionalAssetPaths();

  };

}


