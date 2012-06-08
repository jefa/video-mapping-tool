#ifndef QUADGROUP_H
#define QUADGROUP_H

#include "Quad2D.h"

#include <string>
#include <vector>
using namespace std;

class QuadGroup : public IPropertyManager, ISerializable
{
    public:
        QuadGroup(string name);
        virtual ~QuadGroup();

        string getName();

        void addQuad2D(Quad2D* quad);
        void genUVWCoords();

        virtual float get(int aParam);
        virtual void set(int aParam, float aValue);

        void CalculateBounds();

        vector<Quad2D*> getQuads();

        void SetTextureParams(string key, textureType type);

        virtual SerializedNode* Serialize();
    protected:
    private:
        string name;
        bool enabled;
        vector<Quad2D*> quads2D;
        ofRectangle bounds;
};

#endif // QUADGROUP_H
