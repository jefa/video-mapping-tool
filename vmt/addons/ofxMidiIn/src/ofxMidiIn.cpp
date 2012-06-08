/*
 * ofxMidiIn.cpp
 *
 *  Created on: 15-sep-2008
 *      Author: arturo
 */

#include "ofxMidiIn.h"
#include "../events/ofxMidiEvents.h"


void ofxMidiInCallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
	((ofxMidiIn*)userData)->manageNewMessage(deltatime,message);

}

ofxMidiIn::ofxMidiIn() {
	//eventManager = new ofxMidiEventManager(this);
	//newMessageEvent.init("ofxMidiIn::newMessage");
	//ofEvents::addEvent(newMessageEvent,"ofxMidiIn::newMessage");
	// Check available ports.
	nPorts = midiin.getPortCount();
}

ofxMidiIn::~ofxMidiIn() {
}

void ofxMidiIn::listPorts(){
	printf( " %i ports available \n", nPorts );
	for(unsigned int i=0; i<nPorts; i++){
		printf("%i: %s\n",i,midiin.getPortName(i).c_str());
	}
}

void ofxMidiIn::openPort(unsigned int _port){
	if ( nPorts == 0 ) {
		printf( "No ports available!\n" );
		return;
	}
	if ( _port+1 > nPorts ){
		printf("The selected port is not available\n");
		return;
	}

	port = _port;
	midiin.openPort( port );
	// Set our callback function.  This should be done immediately after
	// opening the port to avoid having incoming messages written to the
	// queue.
	midiin.setCallback( &ofxMidiInCallback, this );

	// Don't ignore sysex, timing, or active sensing messages.
	midiin.ignoreTypes( false, false, false );
}


void ofxMidiIn::manageNewMessage(double deltatime, std::vector< unsigned char > *message){

	unsigned int nBytes = message->size();
	if(bVerbose){
		std::cout << "num bytes: "<<nBytes;
		for ( unsigned int i=0; i<nBytes; i++ )
			std::cout << " Byte " << i << " = " << (int)message->at(i) << ", ";
		if ( nBytes > 0 )
			std::cout << "stamp = " << deltatime << '\n';
	}
    if (nBytes >= 3){
	    ofxMidiEventArgs eventArgs;
	    eventArgs.channel = ((int)message->at(0)) % 16;
	    eventArgs.msgType = ((int)message->at(0)) - eventArgs.channel;
	    eventArgs.channel += 1; // should start at midi channel 1 really
	    eventArgs.id = (int)message->at(1);
	    eventArgs.value = (int)message->at(2);
	    eventArgs.timestamp = deltatime;
		ofNotifyEvent(newMessageEvent,eventArgs,this);
		//ofNotifyEvent(*newIdMessageEvents[eventArgs.id],eventArgs,this);

    }

}
void ofxMidiIn::setVerbose(bool verbose){
	bVerbose=verbose;
}

unsigned int ofxMidiIn::getPort(){
	return port;
}

void ofxMidiIn::addListener(ofxMidiListener* listener){
	ofAddListener(newMessageEvent, listener, &ofxMidiListener::newMidiMessage);
}

void ofxMidiIn::removeListener(ofxMidiListener* listener){
	ofRemoveListener(newMessageEvent, listener, &ofxMidiListener::newMidiMessage);
}

void ofxMidiIn::addListener(int id,ofxMidiListener* listener){
	ofEvent<ofxMidiEventArgs> * event;
	map<int,ofEvent<ofxMidiEventArgs>*>::iterator it=newIdMessageEvents.find(id);
	if(it  == newIdMessageEvents.end()){
		event = new ofEvent<ofxMidiEventArgs>();
		///event->init("ofxMidiIn:" + ofToString(id) +"::newMessage");
		newIdMessageEvents[id]=event;
	}else{
		event=it->second;
	}
	ofAddListener(*event,listener, &ofxMidiListener::newMidiMessage);
}

void ofxMidiIn::removeListener(int id,ofxMidiListener* listener){
	map<int,ofEvent<ofxMidiEventArgs>*>::iterator it=newIdMessageEvents.find(id);
	if(it != newIdMessageEvents.end()){
		ofEvent<ofxMidiEventArgs> * event = it->second;
		ofRemoveListener(*event,listener,&ofxMidiListener::newMidiMessage);
	}
}
