#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "ISerializable.h"

//#include <QTimer>
#include <map>
#include <string>

using namespace std;

enum TIMER_MODE {
	ONE_TIME,
	LOOP
};

class TimeManager : public ISerializable
{
    public:
        TimeManager();
        virtual ~TimeManager();
        void Start(TIMER_MODE mode);
        string Update();
        void ScheduleEvent(float time, string effectId);
        void removeTimeEvent(float time, string effectId);
        map<float, string> getScheduleEvents();
        double getTotalTime();

        virtual SerializedNode* Serialize();
    protected:
    private:
        map<float, string> events;
        map<float, string>::iterator it;

        double totalAnimTime;
        double actualAnimTime;
        double deltaStartTime;       //Tiempo entre que comenzó la aplicación y se hizo init a TimeManager

        float nextTimeEvent;
        float timeOffset;
        bool moreEvents;
        bool started;
        TIMER_MODE playmode;

};

#endif // TIMEMANAGER_H
