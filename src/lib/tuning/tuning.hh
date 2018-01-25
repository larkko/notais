#pragma once

class Tuning
{
  public:
    virtual ~Tuning() {};
    virtual float frequency_at(float steps) const = 0;
};
