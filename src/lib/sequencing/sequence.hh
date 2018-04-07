#pragma once

#include <vector>
#include <algorithm>
#include <cstddef>

#include "../audio/adjustableaudiosource.hh"
#include "../tuning/tuning.hh"
#include "../util/util.hh"

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
        bool is_inside(util::Rectangle<double> rectangle) const;
        void lengthen_by(double amount, double minimum = 0.0);
      private:
        double m_start_point;
        double m_end_point;
        double m_steps;
        double m_velocity;
    };
    
    class Timing
    {
      public:
        Timing(double beats_per_minute);
        double beats_per_minute() const;
        void set_beats_per_minute(double value);
        double to_seconds(double timepoint) const;
      private:
        double m_beats_per_minute;
    };

    class Pattern
    {
      public:
        Pattern(Timing timing = Timing(120));
        void add_note(Note note);
        std::vector<Note> const & notes() const;
        using Index = size_t;
        std::vector<Index> notes_within
        (
            util::Rectangle<double> rectangle
        ) const;
        void remove_notes(std::vector<Index> indices);
        Timing const & timing() const;
        template <typename Function>
        void for_each_in(std::vector<Index> indices, Function function);
      private:
        std::vector<Note> m_notes;
        Timing m_timing;
    };

    Sequence();
    virtual Audio_data::Sample get_sample
    (
        float frequency,
        Offset offset
    ) const final override;
    virtual double linger_time() const final override;
    virtual bool contains(Audio_source const & other) const final override;
    virtual std::string description() const final override;
    void set_instrument(std::shared_ptr<Adjustable_audio_source> instrument);
    void set_tuning(std::shared_ptr<Tuning> tuning);
    std::shared_ptr<Tuning> const & tuning() const;
    Pattern & pattern();
    Pattern const & pattern() const;
  private:
    std::shared_ptr<Adjustable_audio_source> m_instrument;
    std::shared_ptr<Tuning> m_tuning;
    Pattern m_pattern;
};

template <typename Function>
void Sequence::Pattern::for_each_in
(
    std::vector<Sequence::Pattern::Index> indices,
    Function function
)
{
    for(Index i = 0; i < m_notes.size(); ++i)
    {
        if(std::find(indices.begin(), indices.end(), i) != indices.end())
        {
            function(m_notes[i]);
        }
    }
}









