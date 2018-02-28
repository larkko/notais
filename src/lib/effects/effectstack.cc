#include "effectstack.hh"

Effect_stack::Effect_stack()
{

}

void Effect_stack::add_effect(std::shared_ptr<Effect> effect)
{
    m_effects.push_back(effect);
}

Audio_data::Sample Effect_stack::get_sample
(
    Audio_source const & source,
    float frequency,
    Audio_source::Offset offset
) const
{
    return source.get_sample(frequency, offset);
}

double Effect_stack::linger_time() const
{
    double sum = 0.0;
    for(auto & e : m_effects)
    {
        sum += e->linger_time();
    }
    return sum;
}
