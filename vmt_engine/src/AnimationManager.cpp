#include "AnimationManager.h"
#include "ofUtils.h"

vector<Animation*> AnimationManager::playable_animations;
vector<Animation*> AnimationManager::waiting_animations;

AnimationManager::AnimationManager() {
}

AnimationManager::~AnimationManager() {
    //dtor
}

void AnimationManager::PlayAnimation(Animation* anim) {

    bool isAlreadyInPlaylist = false;
    for (unsigned int j = 0; j < AnimationManager::playable_animations.size(); j++) {
        Animation *playable = AnimationManager::playable_animations[j];
        if (playable->equivalent(anim)) {
            isAlreadyInPlaylist = true;
            waiting_animations.push_back(anim);
            break;
        }
    }
    if(!isAlreadyInPlaylist) {
        playable_animations.push_back(anim);
        anim->Start();
    }
}

void AnimationManager::Update() {
    for (unsigned int i = 0; i < playable_animations.size(); i++) {
        Animation *anim = playable_animations[i];
        anim->Update();
        if(!anim->isRunning()) {
            playable_animations.erase(playable_animations.begin() + i);

            //Busco si hay una animacion equivalente esperando
            //y si encuentro una la agrego a playables y la saco de waiting
            for (unsigned int j = 0; j < waiting_animations.size(); j++) {
                Animation *espera = waiting_animations[j];
                if (espera->equivalent(anim)) {
                    playable_animations.push_back(espera);
                    espera->Start();
                    waiting_animations.erase(waiting_animations.begin() + j);
                    break;
                }
            }

            delete anim;
        }
    }
}
