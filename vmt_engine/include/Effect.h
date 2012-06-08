#ifndef EFFECT_H
#define EFFECT_H

#include "ISerializable.h"

enum EFFECT_TYPES {
	POSITION_EFFECT,
	FADE_EFFECT,
	TEXTURE_EFFECT
};

class Effect : public ISerializable
{
    public:
        Effect();
        virtual ~Effect();
        string getId();
        void setId(string);

        virtual void play() = 0;
        virtual void test() = 0;
        virtual int getType() = 0;

        virtual SerializedNode* Serialize() = 0;
        virtual const char* toString() = 0;

    protected:
        string id;
    private:
};

#endif // EFFECT_H
