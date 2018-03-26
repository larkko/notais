#pragma once

#include <vector>

#include "../audio/adjustableaudiosource.hh"
#include "../tuning/tuning.hh"

class Sequence : public Audio_source
{
  public:

    class Note
    {
      public:
        Note
        (
            double start_point,
            double end_point,
            double steps,
            double velocity
        );
        double start_point() const;
        double end_point() const;
        double steps() const;
        double velocity() const;
        double length() const;
      private:
        double m_start_point;
        double m_end_point;
        double m_steps;
        double m_velocity;
    };

    class Pattern
    {
      public:
        Pattern();
        void add_note(Note note);
        std::vector<Note> notes() const;
      private:
        std::vector<Note> m_notes;
    };

    Sequence();
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        Offset offset
    ) const final override;
    virtual double linger_time() const final override;
    void set_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
    void set_tuning(std::shared_ptr<Tuning> tuning);
    Pattern & pattern();
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
    std::shared_ptr<Tuning> m_tuning;
    Pattern m_pattern;
};
