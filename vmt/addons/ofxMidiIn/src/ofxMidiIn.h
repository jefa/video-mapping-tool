/*
 * ofxMidiIn.h
 *
 *  Created on: 15-sep-2008
 *      Author: arturo
 */

#ifndef OFXMIDIIN_H_
#define OFXMIDIIN_H_

#include <iostream>
#include "../libs/RtMidi.h"
#include "../events/ofxMidiEvents.h"
#include "ofMain.h"

#define OFX_MIDI_CONTROL_CHANGE 176
#define OFX_MIDI_NOTE_ON 		144
#define OFX_MIDI_NOTE_OFF		128
#define OFX_MIDI_PITCHBEND		224
#define OFX_MIDI_SYSEX_START	240
#define OFX_MIDI_SYSEX_END		247

class ofxMidiEventManager;
class ofxMidiListener;

void ofxMidiInCallback( double deltatime, std::vector< unsigned char > *message, void *userData );

class ofxMidiIn {
public:
	ofxMidiIn();
	virtual ~ofxMidiIn();

	void listPorts();
	void openPort(unsigned int port=0);
	void manageNewMessage(double deltatime, std::vector< unsigned char > *message);
	unsigned int getPort();
	void setVerbose(bool verbose);

protected:
	RtMidiIn 			midiin;
	unsigned int 		nPorts;
	unsigned int 		port;
	bool				bVerbose;



// events
public:
	void addListener(int id,ofxMidiListener * listener);
	void removeListener(int id,ofxMidiListener * listener);
	void addListener(ofxMidiListener * listener);
	void removeListener(ofxMidiListener * listener);

	map<int,ofEvent<ofxMidiEventArgs>*> 	newIdMessageEvents;
	ofEvent<ofxMidiEventArgs> 				newMessageEvent;



};

#endif /* OFXMIDIIN_H_ */
