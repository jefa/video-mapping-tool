#include "FadeEffect.h"

FadeEffect::FadeEffect(string id, QuadGroup *qg, ofVec4f colorIni, ofVec4f colorFin, float delay) {
    this->id = id;
    this->group = qg;
    this->colorIni = colorIni;
    this->colorFin = colorFin;
    this->delay = delay;
}

FadeEffect::~FadeEffect() {
}

void FadeEffect::play() {
    this->group->set(AMBIENT_R, colorIni.x);
    this->group->set(AMBIENT_G, colorIni.y);
    this->group->set(AMBIENT_B, colorIni.z);
    this->group->set(AMBIENT_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_A, this->delay, this->colorFin.w));
}

void FadeEffect::test() {
    this->group->set(AMBIENT_R, colorIni.x);
    this->group->set(AMBIENT_G, colorIni.y);
    this->group->set(AMBIENT_B, colorIni.z);
    this->group->set(AMBIENT_A, colorIni.w);

    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_R, this->delay, this->colorFin.x));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_G, this->delay, this->colorFin.y));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_B, this->delay, this->colorFin.z));
    AnimationManager::PlayAnimation(new LinearAnimation(this->group, AMBIENT_A, this->delay, this->colorFin.w));
}

int FadeEffect::getType(){
    return FADE_EFFECT;
}

QuadGroup* FadeEffect::getQuadGroup(){
    return this->group;
}

void FadeEffect::setQuadGroup(QuadGroup* grp){
    this->group = grp;
}

ofVec4f FadeEffect::getColorIni(){
    return this->colorIni;
}

void FadeEffect::setColorIni(ofVec4f color){
    this->colorIni = color;
}

ofVec4f FadeEffect::getColorFin(){
    return this->colorFin;
}

void FadeEffect::setColorFin(ofVec4f color){
    this->colorFin = color;
}

float FadeEffect::getDelay(){
    return this->delay;
}

void FadeEffect::setDelay(float f){
    this->delay = f;
}

const char* FadeEffect::toString(){
    string txt = this->id + " : FadeEffect ";//'+colorIni+"::"+colorFin+"::"+delay;
    return txt.c_str();
}

SerializedNode* FadeEffect::Serialize() {
    SerializedNode *node = new SerializedNode("effect");
    node->addAttribute("id", this->id);
    string fadeArg = "fade";
    node->addAttribute("type", fadeArg);
    node->addAttribute("groupid", this->group->getName());

    node->addAttribute("col1", this->colorIni);
    node->addAttribute("col2", this->colorFin);

    node->addAttribute("delay", this->delay);
    return node;
}
