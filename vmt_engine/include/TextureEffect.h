#ifndef TEXTUREEFFECT_H
#define TEXTUREEFFECT_H

#include "Effect.h"
#include "QuadGroup.h"
#include "Object3D.h"
//#include "LinearAnimation.h"

class TextureEffect : public Effect
{
    public:
        TextureEffect(string id, QuadGroup *qg, string texturePath, textureType type);
        TextureEffect(string id, Object3D *obj3d, string facesID, string texturePath, textureType type);
        virtual ~TextureEffect();

        virtual void play();
        virtual void test();
        virtual int getType();
        virtual const char* toString();

        QuadGroup* getGroup();
        void setGroup(QuadGroup*);
        Object3D* getObject3D();
        void setObject3D(Object3D*);
        string getFacesID();
        void setFacesID(string);
        string getTextureKey();
        void setTextureKey(string);
        textureType getTextureType();
        void setTextureType(textureType);
        bool getIsGroup();

        virtual SerializedNode* Serialize();
    protected:
    private:
        QuadGroup* group;
        Object3D* object3d;
        string facesID;

        string textureKey;
        textureType type;

        bool isGroup;
};

#endif // TEXTUREEFFECT_H
