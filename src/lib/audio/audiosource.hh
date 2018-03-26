#pragma once

#include "audiodata.hh"

class Audio_source
{
  public:
    virtual ~Audio_source(){}

    class Offset
    {
      public:
        Offset(double offset, double release_offset = -1.0);
        double offset() const;
        double release_offset() const;
        bool released() const;
        double time_since_release() const;
        operator double() const;
      private:
        double m_offset;
        double m_release_offset;
    };

    virtual Audio_data::Sample get_sample
    (
        float frequency,
        Offset offset
    ) const = 0;

    void get_samples
    (
        Audio_data & destination,
        float frequency,
        float volume,
        size_t sample_count,
        size_t offset_in_source,
        size_t release_offset,
        size_t offset_in_destination
    ) const;

    virtual double linger_time() const;
    
    /*Some audio sources contain other audio sources. Such audio sources
      should override this.*/
    virtual bool contains(Audio_source const & other) const
    {
        return (this == &other);
    }
};
