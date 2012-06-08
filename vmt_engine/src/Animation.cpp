#include "Animation.h"

Animation::Animation(IPropertyManager *pmgr, int propId, double timestamp) {
    propMgr = pmgr;
    propertyId = propId;
    totalAnimationTime = timestamp;
    off = true;
}

void Animation::Start() {
    totalElapsedTime = 0;
    off = false;
}

void Animation::End() {
    off = true;
}

bool Animation::isRunning() {
    return !off;
}

Animation::~Animation() {
    //dtor
}

bool Animation::equivalent(Animation *anim) {
    return (propMgr == anim->propMgr && propertyId == anim->propertyId);
}
