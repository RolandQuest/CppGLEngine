#pragma once

#include <string>

#include "iasset.h"

namespace fml
{

  class iasset_loader
  {

  public:

    virtual iasset* load( const std::string& name, const std::string& assetPath ) = 0;

  };

  class image_asset_loader : public iasset_loader
  {

  public:

    iasset* load( const std::string& name, const std::string& assetPath ) override;

  };

}
