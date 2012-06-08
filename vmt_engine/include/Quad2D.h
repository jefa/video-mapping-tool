#ifndef QUAD2D_H
#define QUAD2D_H

#include "IPropertyManager.h"
#include "ISerializable.h"
#include "Material.h"

#include <string>
using namespace std;

class Quad2D : public IPropertyManager, ISerializable
{
    public:
        Quad2D(float x1 = 100.0f, float y1 = 100.0f, float x2 = 300.0f, float y2 = 100.0f,
               float x3 = 300.0f, float y3 = 300.0f, float x4 = 100.0f, float y4 = 300.0f);

        virtual ~Quad2D();
        virtual void set(int aParam, float value);
        virtual float get(int aParam);
        void draw();
        void setPoint(int i, ofVec2f p);
        void setPoint(int i, float x, float y);
        ofVec2f getPoint(int i);
        void setUVCoordinate(int i, float u, float v);
        int getControlPointAt(int x, int y);
        void setSelected(bool selected);
        void setEnabled(bool enabled);
        bool isEnabled();
        bool isSelected();
        void setId(string id);
        string getId();
        void setMaterial(Material *mat);
        Material* getMaterial();

        virtual SerializedNode* Serialize();

    protected:
    private:
        float quadPoints[8];
        float quadTextCoords[8];
        bool selected;
        bool enabled;
        string id;
        Material *material;
};

#endif // QUAD2D_H
