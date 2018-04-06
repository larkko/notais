#pragma once

#include <string>

class Tuning
{
  public:
    virtual ~Tuning() {};
    virtual float frequency_at(float steps) const = 0;
    virtual int steps_in_pattern() const = 0;
    virtual std::string description() const = 0;
};
