#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "camera/camera.h"
#include "activity/iactivity.h"

class patternPrint : public fml::iactivity
{

private:

  bool** _pattern = nullptr;

  const float _cycle = 10.0;
  float _current = 0.0;

  fml::camera c;

  float zoom = 80.0f;

public:

  patternPrint();
  virtual ~patternPrint();

  //void processInput( float deltaTime );
  void update( float deltaTime ) override;
  void render() override;

  void HandleControls( float deltaTime );

};

