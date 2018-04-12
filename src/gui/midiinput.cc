#include "midiinput.hh"

#include <memory>
#include <iostream>
#include <thread>
#include <array>

#include <alsa/asoundlib.h>

class ALSA_MIDI_input : public MIDI_input_implementation
{
  public:
    ALSA_MIDI_input()
        : m_midi_in(NULL),
          m_port_open(false)
    {
        
    }
    virtual bool open_port(char const * port) override
    {
        int mode = 0;
        int status = snd_rawmidi_open(&m_midi_in, NULL, port, mode);
        bool open_success = status >= 0;
        if(!open_success)
        {
            std::cerr << "Failed to open ALSA rawmidi input."
                         "\nError: " << snd_strerror(status) << std::endl;
            return false;
        }
        else
        {
            m_port_open = true;
            return true;
        }
    }
    virtual bool run(std::function<void (MIDI_event)> callback) override
    {
        if(!m_port_open) return false;
        
        m_thread = 
        std::make_shared<std::thread>
        (
            std::thread
            (
                [=]()
                {
                    std::array<char, 3> data;
                    while(true)
                    {
                        for(auto datum : data)
                        {
                            datum = 0;
                        }
                        auto result = snd_rawmidi_read
                        (
                            m_midi_in,
                            data.data(),
                            data.size()
                        );
                        if(result < 0)
                        {
                            std::cerr << "MIDI input error: " 
                                      << snd_strerror(result) << std::endl;
                        }
                        else
                        {
                            MIDI_event event = MIDI_event::from(data);
                            callback(event);
                        }
                    }
                }
            )
        );
        return true;
    }
    ~ALSA_MIDI_input()
    {
        if(m_port_open)
        {
            snd_rawmidi_close(m_midi_in);
        }
    }
  private:
    snd_rawmidi_t * m_midi_in;
    bool m_port_open;
    std::shared_ptr<std::thread> m_thread;
};


MIDI_input::MIDI_input(std::function<void (MIDI_event)> callback)
    : callback(callback),
      m_implementation(std::make_unique<ALSA_MIDI_input>(ALSA_MIDI_input()))
{
    m_implementation->open_port("hw:1,0,0");
    m_implementation->run(callback);
}
