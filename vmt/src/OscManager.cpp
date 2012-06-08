#include "OscManager.h"

OscManager::OscManager() {
}

void OscManager::Init(map<string, Node*> network)
{
    senders.clear();

    map<string, Node*>::iterator iter = network.begin();
    while (iter != network.end() )
    {
        string nName = iter->first;
        Node *n = (Node*)iter->second;
        ofLog(OF_LOG_VERBOSE, "OscManager:: Detected node %s:%d", n->address.c_str(), n->port);

        ofxOscSender *sender = new ofxOscSender();
        sender->setup(n->address, n->port);
        senders.insert (pair<string, ofxOscSender*>(nName, sender));
        iter++;
    }
    //receiver.setup( 12345 );
    ofLog(OF_LOG_VERBOSE, "OscManager:: Configured!");
}

OscManager::~OscManager()
{
     ofLog(OF_LOG_VERBOSE, "OscManager:: Destroying...");
}

void OscManager::SendMessage(ofxOscMessage oscMessage, string destNode)
{
    ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message: type=%s", oscMessage.getAddress().c_str());

    if (!destNode.empty()){
        ofLog(OF_LOG_VERBOSE, "OscManager:: sending to specific node '%s'", destNode.c_str());
        getSender(destNode.c_str())->sendMessage( oscMessage );
    } else {
        ofLog(OF_LOG_VERBOSE, "OscManager:: node empty!");
    }
}

void OscManager::SendMessageAll(ofxOscMessage oscMessage)
{
    ofLog(OF_LOG_VERBOSE, "OscManager:: Sending message to ALL: type=%s", oscMessage.getAddress().c_str());
    map<string, ofxOscSender*>::iterator iter = senders.begin();
    while (iter != senders.end()) {
        iter->second->sendMessage( oscMessage );
        iter++;
    }
}

void OscManager::checkForMessages()
{
    string msg_string;

    ofLog(OF_LOG_VERBOSE, "OscManager: Checking for messages...\n");
    /*while( receiver.hasWaitingMessages() )
    {
        ofxOscMessage m;
        receiver.getNextMessage( &m );
        EventArg *evtArg = new EventArg();
        evtArg->args = m;

        map<string, IEventListener*>::iterator iter = listeners.begin();
        while (iter != listeners.end() )
        {
            iter->second->event(evtArg);
            iter++;
        }
    }*/
}

ofxOscSender* OscManager::getSender(string nodeName){
    map<string, ofxOscSender*>::iterator s = senders.find(nodeName);
    if(s != senders.end())
        return s->second;
    else
        ofLog(OF_LOG_WARNING, "OscManager:: In getSender cannot find node for name '"+nodeName+"'");
    return NULL;
}
