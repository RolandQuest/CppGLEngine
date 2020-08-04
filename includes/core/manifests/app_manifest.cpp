#include "app_manifest.h"

#include "log/log.h"

namespace fml
{

  app_manifest::app_manifest( json& config ) {

    _entry = config[entryKey];
    
    for ( auto& act : config[activitiesKey].items() ) {

      std::string pathName = act.value()[manifestKey];
      json activityManifestJson;

      if ( supp::load_json( pathName, activityManifestJson ) ) {
        activity_manifest* manifest = new activity_manifest( act.key(), activityManifestJson );
        _activities[act.key()] = manifest;
      }
    }
    
  }

  app_manifest::~app_manifest() {
    for ( auto p : _activities ) {
      delete p.second;
    }
  }

  activity_manifest* app_manifest::getActivityManifest( const std::string& name ) {
    return _activities[name];
  }

  activity_manifest* app_manifest::getEntryActivityManifest() {
    return _activities[_entry];
  }

}
