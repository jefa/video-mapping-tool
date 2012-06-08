#ifndef ANIMATION_H
#define ANIMATION_H

#include "IPropertyManager.h"

class Animation
{
    public:
        Animation(IPropertyManager *pmgr, int propertyId, double timestamp);
        virtual ~Animation();

        /**
        Returns true if this animation and anim have the same IPropertyManager and propertyId.
        */
        bool equivalent(Animation *anim);
        virtual void Update()=0;
        virtual void Start();
        virtual void End();
        bool isRunning();

    protected:
        IPropertyManager *propMgr;
        int propertyId;
        double totalElapsedTime;
        double totalAnimationTime;

    private:
        bool off;

};

#endif // ANIMATION_H
