/*
 * ofxMidiEvents.h
 *
 *  Created on: 15-sep-2008
 *      Author: art
 */

#ifndef OFXMIDIEVENTS_H_
#define OFXMIDIEVENTS_H_

#include "ofMain.h"
#include "ofEvents.h"
#include <map>



class ofxMidiEventArgs: public ofEventArgs{
public:
	int 	port;
	int 	id;
	int 	value;
	int		channel;
	int 	msgType;
	double 	timestamp;
};

typedef ofEvent<ofxMidiEventArgs> ofxMidiEvent ;


class ofxMidiListener {
public:
	ofxMidiListener(){}
	virtual ~ofxMidiListener(){}

	//virtual void newMidiMessage(ofxMidiEventArgs& eventArgs);
	virtual void newMidiMessage(ofxMidiEventArgs& eventArgs)=0;
	//void newMidiMessage(ofxMidiEventArgs& eventArgs);

};


#endif /* OFXMIDIEVENTS_H_ */
