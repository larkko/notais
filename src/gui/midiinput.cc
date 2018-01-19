#include "midiinput.hh"

MIDI_input::MIDI_input()
    : m_midi_in(RtMidiIn())
{
    int port_count = m_midi_in.getPortCount();
    if(port_count == 0)
    {
        std::cout << "No MIDI input ports found.\n" << std::endl;
    }
    else
    {
        m_midi_in.openPort(1);

        m_midi_in.setCallback
        (
            [](double timestamp,
            std::vector<unsigned char> * message,
            void * user_data)
            {
                std::cout << "Got something" << std::endl;
            }
        );
        m_midi_in.ignoreTypes(false,false,false);
    }
}