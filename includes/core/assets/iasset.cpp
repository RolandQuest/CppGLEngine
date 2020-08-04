#include "iasset.h"

namespace fml
{


  iasset::iasset( const std::string& name ) {
    _assetName = name;
  }

  const std::string& iasset::GetName() {
    return _assetName;
  }


}