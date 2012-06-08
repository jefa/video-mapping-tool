#ifndef KEYEVENTSMANAGER_H
#define KEYEVENTSMANAGER_H

#include "ISerializable.h"

#include <string>
#include <map>
using namespace std;

class KeyEventsManager : public ISerializable
{
    public:
        KeyEventsManager();
        virtual ~KeyEventsManager();

        void addKeyEvent(char key, string effectId);
        void removeKeyEvent(char key, string effectId);
        bool hasKeyEvent(char key);
        string getEffectId(char key);
        map<char, string> getKeyEvents();

        virtual SerializedNode* Serialize();

    protected:
    private:
        map<char, string> events;
};

#endif // KEYEVENTSMANAGER_H
