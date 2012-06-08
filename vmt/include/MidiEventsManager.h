#ifndef MIDIEVENTSMANAGER_H
#define MIDIEVENTSMANAGER_H

#include "ISerializable.h"

#include <string>
#include <map>
#include "..\addons\ofxMidiIn\events\ofxMidiEvents.h"

using namespace std;

class MidiEventsManager : public ISerializable{

    public:
        MidiEventsManager();
        virtual ~MidiEventsManager();

        void addMidiEvent(ofxMidiEventArgs*	msg, string effectId);
        void removeMidiEvent(ofxMidiEventArgs*	msg, string effectId);
        bool hasMidiEvent(ofxMidiEventArgs*	msg);
        string getEffectId(ofxMidiEventArgs*	msg);
        map<ofxMidiEventArgs*, string> getMidiEvents();

        virtual SerializedNode* Serialize();


    private:

        map<ofxMidiEventArgs*, string> events;
};

#endif // MIDIEVENTSMANAGER_H
