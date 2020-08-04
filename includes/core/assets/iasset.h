#pragma once

#include <string>

namespace fml
{

  class iasset
  {

  private:

    std::string _assetName;

  public:

    iasset( const std::string& name );

    const std::string& GetName();



  };


}