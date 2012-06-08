#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "Animation.h"

#include <vector>
using namespace std;

class AnimationManager
{
    public:
        AnimationManager();
        virtual ~AnimationManager();
        static void PlayAnimation(Animation* anim);
        static void Update();
    protected:
    private:
        static vector<Animation*> playable_animations;
        static vector<Animation*> waiting_animations;

};

#endif // ANIMATIONMANAGER_H
