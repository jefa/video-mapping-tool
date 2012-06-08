#include "qdatastream.h"
#include "qmetatype.h"
#include "qtextstream.h"
#include <QtGui>

#include "vmt.h"
#include <map>

//--------------------------------------------------------------

Vmt::Vmt() : ofBaseApp() {
     midiIn.listPorts();
     midiIn.openPort(0);

     addMidiListener(this);
     midiIn.setVerbose(true);
}

void Vmt::setup(){

    ofSetLogLevel(OF_LOG_WARNING);

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled

    vmtModel = new VmtModel();
    vmtModel->loadShow("./showCubos.XML");

    //vmtModel->saveShow("showYYY.XML");

    treeWindow = new TreeWindow(this->vmtModel);
    treeWindow->show();

    effectsWindow = new EffectsListWindow(this->vmtModel);
    effectsWindow->show();

    evteffectsWind = new evtEffectsListWindow(this->vmtModel);
    evteffectsWind->show();

    //evteffectsWindkey = new keyEffectsListWindow(this->vmtModel);
    //evteffectsWindkey->show();

    //timelineWindow = new timeline(this->vmtModel);
    //timelineWindow->show();
}

//--------------------------------------------------------------
void Vmt::update(){
    this->vmtModel->update();
}

//--------------------------------------------------------------
void Vmt::draw(){
    //Draw scene
    this->vmtModel->draw();
}

//--------------------------------------------------------------

void Vmt::keyPressed(int key){

    if (vmtModel->hasKeyEvent(key)) {
        vmtModel->testEffect(vmtModel->getEffectIdForKeyEvent(key));
    }

    if(key == 'p')
        vmtModel->startTimeManager(ONE_TIME);

    if(key == '0')
        vmtModel->resetScene();

    if(key == '1')
        vmtModel->activateCamera("cam1");

    if(key == '2')
        vmtModel->activateCamera("cam2");
}

//--------------------------------------------------------------
void Vmt::newMidiMessage(ofxMidiEventArgs& eventArgs){
    	cout<<"MidiEventsManager::newMidiMessage"<<eventArgs.id <<" "<< eventArgs.value  << '\n';
    ofxMidiEventArgs * msg = new ofxMidiEventArgs();
    msg->channel = eventArgs.channel;
    msg->id = eventArgs.id;
    msg->msgType = eventArgs.msgType;
    msg->port = eventArgs.port;
    msg->timestamp = eventArgs.timestamp;
    msg->value = eventArgs.value;
    vmtModel->testEffect("ef1"/*efecto 1 hardcode*/);
    if (vmtModel->hasMidiEvent(msg)) {
        vmtModel->testEffect(vmtModel->getEffectIdForMidiEvent(msg));
    }

}
//--------------------------------------------------------------

void Vmt::addMidiListener(ofxMidiListener *listener){
    midiIn.addListener(listener);
}
//--------------------------------------------------------------
void Vmt::keyReleased(int key){
}

//--------------------------------------------------------------
void Vmt::mouseMoved(int x, int y ){
}

int xMouseDown, yMouseDown;



//--------------------------------------------------------------
void Vmt::mouseDragged(int x, int y, int button){
    int dx = x - xMouseDown;
    int dy = y - yMouseDown;

    xMouseDown = x;
    yMouseDown = y;

    switch(vmtModel->getControlMode()) {
        case ORBIT_MODE:
            vmtModel->OrbitActiveCamera(dx,dy);
            break;
        case ROLL_MODE:
            vmtModel->RollActiveCamera(dx);
            break;
        case DOLLY_MODE:
            vmtModel->DollyActiveCamera(dy);
            break;
        case PAN_MODE:
            vmtModel->PanActiveCamera(dx, dy);
            break;
    }

}

//--------------------------------------------------------------
void Vmt::mousePressed(int x, int y, int button){
    xMouseDown = x;
    yMouseDown = y;
}

//--------------------------------------------------------------
void Vmt::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
