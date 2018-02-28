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
    return get_sample_nested(source, frequency, offset, 0);
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

Audio_data::Sample Effect_stack::get_sample_nested
(
    Audio_source const & source,
    float frequency,
    Audio_source::Offset offset,
    size_t effect_index
) const
{
    if(m_effects.empty())
    {
        return source.get_sample(frequency, offset);
    }
    else
    {
        if(effect_index >= m_effects.size())
        {
            return source.get_sample(frequency, offset);
        }
        else
        {
            struct Effect_proxy : public Audio_source
            {
                Audio_source const & source;
                Effect const & effect;
                Effect_proxy(Audio_source const & source, Effect const & effect)
                    : source(source), effect(effect) {}
                virtual Audio_data::Sample get_sample
                (
                    float frequency,
                    Audio_source::Offset offset
                ) const final override
                {
                    return effect.get_sample(source, frequency, offset);
                }
            };
            Effect_proxy proxy(source, *(m_effects[effect_index]));
            return get_sample_nested(proxy, frequency, offset, effect_index + 1);
        }
    }
}



