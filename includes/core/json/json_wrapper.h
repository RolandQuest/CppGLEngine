#pragma once

#include <string>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace fml
{
  namespace supp
  {

    inline bool load_json( const std::string& fileName, json& container ) {

      std::ifstream stream( fileName );

      if ( !stream.is_open() ) {
        return false;
      }

      stream >> container;
      stream.close();
      return true;
    }

  }

}

