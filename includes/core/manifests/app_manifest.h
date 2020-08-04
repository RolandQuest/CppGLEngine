#pragma once

#include <map>
#include <string>

#include "json/json_wrapper.h"
#include "manifests/activity_manifest.h"

namespace fml
{

  class app_manifest
  {

  private:

    const std::string activitiesKey = "activities";
    const std::string entryKey = "entry";
    const std::string manifestKey = "manifest";

    std::string _entry;
    std::map<std::string, activity_manifest*> _activities;

  public:

    app_manifest( json& config );
    virtual ~app_manifest();

    activity_manifest* getActivityManifest( const std::string& name );
    activity_manifest* getEntryActivityManifest();

  };

}

