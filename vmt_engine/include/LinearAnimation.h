#ifndef LINEARANIMATION_H
#define LINEARANIMATION_H

#include "Animation.h"

class LinearAnimation : public Animation
{
    public:
        LinearAnimation(IPropertyManager *pmgr, int propertyId, double timeSeconds, float targetValue);
        virtual ~LinearAnimation();
        virtual void Update();
        virtual void Start();
        virtual void End();
    protected:
    private:
        float targetVal;
        float initValue;
};

#endif // LINEARANIMATION_H
