#ifndef LAYER2D_H
#define LAYER2D_H

#include "Quad2D.h"

#include <string>
#include <vector>
#include <map>
using namespace std;

class Layer2D : public ISerializable
{
    public:
        Layer2D();
        Layer2D(string name);
        virtual ~Layer2D();

        Quad2D* addQuad2D(string id);
        Quad2D* getQuad2D(string id);
        map<string, Quad2D*> getQuads2D();

        void draw();
        void setEnabled(bool enabled);
        void setName(string name);
        bool isEnabled();
        string getName();

        virtual SerializedNode* Serialize();

    private:
        string name;
        bool enabled;
        map<string, Quad2D*> quads2D_map;

};

#endif // LAYER2D_H
