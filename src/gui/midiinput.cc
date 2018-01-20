#include "midiinput.hh"

MIDI_input::MIDI_input(std::function<void (Event)> callback)
    : callback(callback),
      m_midi_in(RtMidiIn())
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
                (void)timestamp;
                MIDI_input * input = static_cast<MIDI_input *>(user_data);
                Event event = input->as_event(message);
                input->callback(event);
            },
            /*user_data pointer for callback*/
            this
        );
        m_midi_in.ignoreTypes(false,false,false);
    }
}

MIDI_input::Event MIDI_input::as_event(std::vector<unsigned char> * message)
{
    if(message->size() >= 3)
    {
        bool down = message->at(0) == 144;
        int key = message->at(1);
        float velocity = (float)(message->at(2)) / 128.0f;
        return {down, key, velocity};
    }
    else
    {
        return {false, 0, 0.0f};
    }
}