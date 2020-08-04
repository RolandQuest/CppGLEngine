#include "asset_manager.h"

namespace fml
{

  namespace asset_manager
  {
    namespace {

      std::map<std::string, iasset*> _assets;

      std::map< std::string, iasset_loader*> _loaders {
        { "image", nullptr },
        { "json", nullptr }
      };

    }

    bool isAssetLoaded( const std::string& assetName ) {
      return _assets.count( assetName ) == 1;
    }

    bool loadAsset( const std::string& type, const std::string& assetName, const std::string& assetPath ) {

      if ( _loaders[type] == nullptr ) {
        return false;
      }

      iasset* a = _loaders[type]->load( assetName, assetPath );
      _assets[assetName] = a;
      return true;
    }

    void registerLoader( const std::string& type, iasset_loader* loader ) {
      if ( _loaders[type] != nullptr ) {
        delete _loaders[type];
      }
      _loaders[type] = loader;
    }

    void unLoadAsset( const std::string& assetName ) {
      if ( isAssetLoaded( assetName ) ) {
        delete _assets[assetName];
        _assets.erase( assetName );
      }
    }

    iasset* getAsset( const std::string& assetName ) {
      if ( !isAssetLoaded( assetName ) ) {
        return nullptr;
      }
      return _assets[assetName];
    }

    size_t assetCount() {
      return _assets.size();
    }

  }

}
