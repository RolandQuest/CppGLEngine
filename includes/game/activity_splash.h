#pragma once

#include "manifests/activity_manifest.h"
#include "activity/iactivity.h"
#include "math/interpolator_linear.h"

class activity_splash : public fml::iactivity
{

private:

  fml::interpolator_linear* _fade;



public:

  activity_splash();
  virtual ~activity_splash() = default;

  void load( fml::activity_manifest* manifest ) override;

  void update( float deltaTime ) override;

  void render() override;

};

