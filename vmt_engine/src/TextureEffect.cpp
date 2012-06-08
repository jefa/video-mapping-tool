#include "TextureEffect.h"

TextureEffect::TextureEffect(string id, QuadGroup *qg, string texturePath, textureType type) {
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(texturePath, texturePath);
            TextureManager::PlayVideo(texturePath, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(texturePath, texturePath);
            break;
    }
    this->id = id;
    this->group = qg;
    this->textureKey = texturePath;
    this->type = type;
    this->isGroup = true;
}

TextureEffect::TextureEffect(string id, Object3D *obj3d, string facesID, string texturePath, textureType type) {
    switch(type) {
        case VIDEO_TEXTURE:
            TextureManager::LoadVideoTexture(texturePath, texturePath);
            TextureManager::PlayVideo(texturePath, 1);
            break;
        case IMAGE_TEXTURE:
            TextureManager::LoadImageTexture(texturePath, texturePath);
            break;
    }

    this->id = id;
    this->object3d = obj3d;
    this->facesID = facesID;
    this->textureKey = texturePath;
    this->type = type;
    this->isGroup = false;
}

TextureEffect::~TextureEffect()
{
    //dtor
}

void TextureEffect::play() {
}

void TextureEffect::test() {
    if(isGroup)
        this->group->SetTextureParams(this->textureKey, this->type);
    else {
        this->object3d->SetTextureParamsForMaterial(this->facesID, this->textureKey, this->type);
    }
}

int TextureEffect::getType(){
    return TEXTURE_EFFECT;
}

QuadGroup* TextureEffect::getGroup(){
    return this->group;
}

void TextureEffect::setGroup(QuadGroup* grp){
    this->group = grp;
}

Object3D* TextureEffect::getObject3D(){
    return this->object3d;
}

void TextureEffect::setObject3D(Object3D* obj){
    this->object3d = obj;
}

string TextureEffect::getFacesID(){
    return this->facesID;
}

void TextureEffect::setFacesID(string faces){
    this->facesID = faces;
}

string TextureEffect::getTextureKey(){
    return this->textureKey;
}

void TextureEffect::setTextureKey(string key){
    this->textureKey = key;
}

textureType TextureEffect::getTextureType(){
    return this->type;
}

void TextureEffect::setTextureType(textureType type){
    this->type = type;
}

bool TextureEffect::getIsGroup(){
    return this->isGroup;
}


const char* TextureEffect::toString(){
    string txt = this->id + " : TextureEffect : ";//+facesID+"::"+textureKey+"::"+isGroup+"::";
    if (isGroup){
        txt = txt+ group->getName();
    } else {
        txt = txt+ object3d->getId();
    }
    return txt.c_str();
}

SerializedNode* TextureEffect::Serialize() {
    SerializedNode *node = new SerializedNode("effect");
    node->addAttribute("id", this->id);

    if(this->isGroup) {
        string groupTextureArg = "grouptexture";
        node->addAttribute("type", groupTextureArg);
        node->addAttribute("groupid", this->group->getName());
        node->addAttribute("texturename", this->textureKey);
    }
    else {
        string object3dtextureArg = "object3dtexture";
        node->addAttribute("type", object3dtextureArg);
        node->addAttribute("objid", this->object3d->getId());
        node->addAttribute("texturename", this->textureKey);
        node->addAttribute("facesid", this->facesID);
        node->addAttribute("texturename", this->textureKey);
    }

    if(this->type == VIDEO_TEXTURE) {
        string videotextureArg = "VIDEO_TEXTURE";
        node->addAttribute("texturetype", videotextureArg);
    }
    else {
        string imagetextureArg = "IMAGE_TEXTURE";
        node->addAttribute("texturetype", imagetextureArg);
    }


    return node;
}
