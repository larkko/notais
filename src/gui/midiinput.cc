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
        /*MIDI "note on" event when first byte is 1001**** */
        bool down = (message->at(0) & 0b11110000) == 0b10010000;
        /*The key being struct is at byte number two*/
        int key = message->at(1);
        /*The velocity of the strike is the 7 least significant bits
          of the third byte (normalized to a float [0,1] here).*/
        float velocity = (float)(message->at(2)) / (float)0b01111111;
        return {down, key, velocity};
    }
    else
    {
        return {false, 0, 0.0f};
    }
}