#include "TextureManager.h"

map<string, ofImage*> TextureManager::imageTextures;
map<string, ofxAlphaVideoPlayer*> TextureManager::videoTextures;

TextureManager::TextureManager() {
    //ctor
}

TextureManager::~TextureManager() {
    //dtor
}

void TextureManager::LoadImageTexture(string key, string path) {
    ofDisableArbTex();
    ofImage * image = new ofImage();
    image->loadImage(path);
    imageTextures.insert(pair<string, ofImage*>(key, image));
}

void TextureManager::LoadVideoTexture(string key, string path) {
    ofDisableArbTex();
    ofxAlphaVideoPlayer *video = new ofxAlphaVideoPlayer();
    video->loadMovie(path);
    videoTextures.insert(pair<string, ofxAlphaVideoPlayer*>(key, video));
}

void TextureManager::UnloadVideoTexture(string key) {
    videoTextures.erase(key);
}

void TextureManager::Update() {
    map<string, ofxAlphaVideoPlayer*>::iterator it;
    for(it = videoTextures.begin(); it != videoTextures.end(); ++it) {
        (*it).second->idleMovie();
    }
}

void TextureManager::PlayVideo(string key, float speed) {
    if (GetVideoTexture(key) == NULL){
        ofLog(OF_LOG_ERROR, "TextureManager: Cannot play video %s", key.c_str());
        return;
    }
    ofLog(OF_LOG_NOTICE, "TextureManager: Video %s found", key.c_str());
    GetVideoTexture(key)->play();
    GetVideoTexture(key)->setSpeed(speed);
}

void TextureManager::StopVideo(string key) {
    if (GetVideoTexture(key) == NULL){
        ofLog(OF_LOG_ERROR, "TextureManager: Cannot stop video %s", key.c_str());
        return;
    }
    GetVideoTexture(key)->stop();
}

bool TextureManager::IsTextureReady(string key, textureType type) {
    if(type == VIDEO_TEXTURE) {
        ofxAlphaVideoPlayer *vid = GetVideoTexture(key);
        if (vid == NULL){
            ofLog(OF_LOG_ERROR, "TextureManager: TextureReady video not found: %s", key.c_str());
            return false;
        }
        return vid->isPlaying();
    }
    return true;
}

ofTexture& TextureManager::GetTextureReference(string key, textureType type) {
    if(type == IMAGE_TEXTURE) {
        ofImage *image = GetImageTexture(key);
        if (image == NULL){
            ofLog(OF_LOG_ERROR, "TextureManager: Texture image not found: %s", key.c_str());
            throw exception();
        }
        image->update();
        image->draw(0,0,0,0);//POSIBLE HACK;
        return image->getTextureReference();
    }
    else if (type == VIDEO_TEXTURE) {
        ofxAlphaVideoPlayer *vid = GetVideoTexture(key);
        if (vid == NULL){
            ofLog(OF_LOG_ERROR, "TextureManager: Texture video not found: %s", key.c_str());
            throw exception();
        }
        vid->draw(0,0,0,0); //HACK: la textura se actualiza con este draw
        return vid->getTextureReference();
    }
    throw exception();
}

ofxAlphaVideoPlayer* TextureManager::GetVideoTexture(string key){
    map<string, ofxAlphaVideoPlayer*>::iterator it = videoTextures.find(key);
    if(it != videoTextures.end()) {
       return it->second;
    }
    ofLog(OF_LOG_ERROR, "TextureManager - texture %s not found.", key.c_str());
    return NULL;
}

ofImage* TextureManager::GetImageTexture(string key){
    map<string, ofImage*>::iterator it = imageTextures.find(key);
    if(it != imageTextures.end()) {
       return it->second;
    }
    ofLog(OF_LOG_ERROR, "TextureManager - texture %s not found.", key.c_str());
    return NULL;
}
