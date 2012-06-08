#ifndef SERIALIZEDNODE_H
#define SERIALIZEDNODE_H

#include <vector>
#include <string>
#include "..\addons\ofxMidiIn\events\ofxMidiEvents.h"
using namespace std;

class SerializedNode
{
    public:
        SerializedNode(string tagId);
        virtual ~SerializedNode();

        string getTagId();
        vector<pair<string, string> > getAttributes();
        vector<SerializedNode*> getChildNodes();

        void addAttribute(string attrId, string attrVal);
        void addAttribute(string attrId, int attrVal);
        void addAttribute(string attrId, float attrVal);
        void addAttribute(string attrId, bool attrVal);
        void addAttribute(string attrId, ofVec2f attrVal);
        void addAttribute(string attrId, ofVec3f attrVal);
        void addAttribute(string attrId, ofVec4f attrVal);
        void addAttribute(string attrId, ofxMidiEventArgs* attrVal);

        void addChildNode(SerializedNode* child);

    protected:
    private:
        string tagId;
        vector<pair<string, string> > attributes;
        vector<SerializedNode*> childNodes;
};

#endif // SERIALIZEDNODE_H
