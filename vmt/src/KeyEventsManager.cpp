#include "KeyEventsManager.h"

KeyEventsManager::KeyEventsManager()
{
    //ctor
}

KeyEventsManager::~KeyEventsManager()
{
    //dtor
}

void KeyEventsManager::addKeyEvent(char key, string effectId) {
    events.insert(pair<char,string>(key,effectId));
    map<char, string>::iterator keyeffectsIt;
    for(keyeffectsIt = events.begin(); keyeffectsIt != events.end(); keyeffectsIt++) {
    cout << (*keyeffectsIt).first << " => " << (*keyeffectsIt).second << endl;}
}
void KeyEventsManager::removeKeyEvent(char key, string effectId) {
    map<char, string>::iterator keyeffectsIt;
    for(keyeffectsIt = events.begin(); keyeffectsIt != events.end(); keyeffectsIt++) {
        if (keyeffectsIt->second == effectId & keyeffectsIt->first == key) {
            events.erase(keyeffectsIt);
            return;
        }
    }
}
bool KeyEventsManager::hasKeyEvent(char key) {
    return events.count(key) > 0;
}

string KeyEventsManager::getEffectId(char key) {
    return events[key];
}

SerializedNode* KeyEventsManager::Serialize() {
    SerializedNode *node = new SerializedNode("keyevents");

    map<char, string>::iterator eventsIt;
    for(eventsIt = events.begin(); eventsIt != events.end(); eventsIt++) {
        SerializedNode *eventNode = new SerializedNode("keyevent");
        eventNode->addAttribute("key", eventsIt->first);
        eventNode->addAttribute("effect", eventsIt->second);
        node->addChildNode(eventNode);
    }

    return node;
}

map<char, string> KeyEventsManager::getKeyEvents(){
    return events;
}
