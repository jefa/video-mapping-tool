#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "Effect.h"
#include "QuadGroup.h"
#include "AnimationManager.h"
#include "LinearAnimation.h"

class FadeEffect : public Effect
{
    public:
        FadeEffect(string id, QuadGroup *qg, ofVec4f colorIni, ofVec4f colorFin, float delay);
        virtual ~FadeEffect();

        virtual void play();
        virtual void test();
        virtual int getType();
        virtual const char* toString();

        QuadGroup* getQuadGroup();
        void setQuadGroup(QuadGroup*);
        ofVec4f getColorIni();
        void setColorIni(ofVec4f);
        ofVec4f getColorFin();
        void setColorFin(ofVec4f);
        float getDelay();
        void setDelay(float);

        virtual SerializedNode* Serialize();
    protected:
    private:
        QuadGroup *group;
        ofVec4f colorIni;
        ofVec4f colorFin;
        float delay;

};

#endif // FADEEFFECT_H
