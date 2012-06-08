#include "TimeManager.h"
#include "ofAppRunner.h"

TimeManager::TimeManager() {
    started = false;
}

TimeManager::~TimeManager() {
}

double TimeManager::getTotalTime(){
    return this->totalAnimTime;
}

void TimeManager::Start(TIMER_MODE mode) {
    playmode = mode;
    actualAnimTime = 0;
    //totalAnimTime = 0;

    if(events.size() > 0) {
        it = events.begin();
        nextTimeEvent = it->first;
        moreEvents = true;
    }
    else {
        moreEvents = false;
    }

    deltaStartTime = ofGetElapsedTimef();
    started = true;
}

void TimeManager::ScheduleEvent(float time, string effectId) {
    moreEvents = true;
    float time_fixed = time;
    while(events.count(time_fixed) > 0) {
        time_fixed += 0.001f;
    }
    events.insert(make_pair(time_fixed, effectId));

    if (time > totalAnimTime)
        totalAnimTime = time + 1; //add one second to the last added event
}
void TimeManager::removeTimeEvent(float time, string effectId) {
    map<float, string>::iterator timeeffectsIt;
    for(timeeffectsIt = events.begin(); timeeffectsIt != events.end(); timeeffectsIt++) {
        if (timeeffectsIt->second == effectId & timeeffectsIt->first == time) {
            events.erase(timeeffectsIt);
            return;
        }
    }
}

map<float, string> TimeManager::getScheduleEvents() {
    return events;
}

string TimeManager::Update() {
    string effectId = "";

    if(!started)
        return effectId;

    actualAnimTime = ofGetElapsedTimef() - deltaStartTime;

    if(moreEvents && events.size() > 0 && actualAnimTime > nextTimeEvent) {
        effectId = it->second;
        ++it;
        if(it == events.end()) {
            moreEvents = false;
            if(playmode == LOOP) {
                deltaStartTime = ofGetElapsedTimef();
                it = events.begin();
                nextTimeEvent = it->first;
                if(events.size() > 0)
                    moreEvents = true;
            }
        }
        else {
            nextTimeEvent = it->first;
        }
    }

    return effectId;
}

SerializedNode* TimeManager::Serialize() {
    SerializedNode *node = new SerializedNode("timedevents");

    map<float, string>::iterator eventsIt;
    for(eventsIt = events.begin(); eventsIt != events.end(); eventsIt++) {
        SerializedNode *eventNode = new SerializedNode("timedevent");
        eventNode->addAttribute("t", eventsIt->first);
        eventNode->addAttribute("effect", eventsIt->second);
        node->addChildNode(eventNode);
    }

    return node;
}
