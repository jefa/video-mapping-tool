#ifndef SCENE_H
#define SCENE_H

#include "ISerializable.h"
#include "ofxCamera.h"
#include "ofxLight.h"
#include "Object3D.h"
#include "Effect.h"
#include "QuadGroup.h"
#include <string>
#include <map>
using namespace std;

class Scene : public ISerializable
{
    public:
        Scene();
        virtual ~Scene();

        void draw();
        void update();
        void setBackground(float r, float g, float b);
        ofxCamera* addCamera(string id);
        ofxCamera* getCamera(string id);
        ofxCamera* activateCamera(string id);
        ofxCamera* getActiveCamera();
        map<string, ofxCamera*> getCameras();
        map<string, ofxLight*> getLights();

        ofxLight* addLight(string id);
        ofxLight* getLight(string id);
        void setLightOn(string lightId);
        void setLightOff(string lightId);

        Object3D* addObject3D(string id, string path);
        void setObject3D(string id,int aParam, float aValue);
        Object3D* getObject3D(string id);
        map<string, Object3D*> getObjects3D();
        Object3D* activateObject(string id);
        Object3D* getActiveObject();
        void deActivateObject();

        QuadGroup* addGroup(string id);
        QuadGroup* getGroup(string id);

        map<string, QuadGroup*> getGroups();

        Effect* addEffect(string id, Effect* effect);
        map<string, Effect*> getEffects();
        map<string, float> getEvtEffects();
        map<string, string> getKeyEffects();
        void testEffect(string id);

        SerializedNode* Serialize();
    private:
        map<string, ofxCamera*> cameras;
        ofxCamera* activeCamera;
        Object3D* activeObject;
        map<string, ofxLight*> lights;
        map<string, Object3D*> objects3D;
        map<string, QuadGroup*> quadGroups;
        map<string, Effect*> effects;
        ofVec3f bgColor;
};

#endif // SCENE_H
