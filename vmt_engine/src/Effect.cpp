#include "Effect.h"

Effect::Effect()
{
    //ctor
}

Effect::~Effect()
{
    //dtor
}

string Effect::getId(){
    return this->id;
}

void Effect::setId(string id){
    this->id = id;
}
