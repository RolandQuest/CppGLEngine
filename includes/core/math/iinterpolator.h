#pragma once

namespace fml
{

  class iinterpolator
  {

  protected:

    float _totalTime;
    float _sumTime = 0.0;

  public:

    iinterpolator( float time );

    virtual ~iinterpolator() = default;

    bool isComplete();

    virtual void reset();

    virtual void update( float deltaTime );

    virtual float getValue() = 0;

  };


}

