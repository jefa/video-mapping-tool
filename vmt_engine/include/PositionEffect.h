#ifndef POSITIONEFFECT_H
#define POSITIONEFFECT_H

#include "Effect.h"
#include "Object3D.h"

class PositionEffect : public Effect
{
    public:
        PositionEffect(string id, Object3D *obj, ofVec3f posIni, ofVec3f posFin, float delay);
        virtual ~PositionEffect();

        virtual void play();
        virtual void test();
        virtual int getType();
        virtual const char* toString();

        Object3D* getObject3D();
        void setObject3D(Object3D*);
        ofVec3f getPosIni();
        void setPosIni(ofVec3f);
        ofVec3f getPosFin();
        void setPosFin(ofVec3f);
        float getDelay();
        void setDelay(float);

        virtual SerializedNode* Serialize();

    protected:
    private:
        Object3D *object3d;
        ofVec3f posIni;
        ofVec3f posFin;
        float delay;
};

#endif // POSITIONEFFECT_H
