#include "Scene.h"
#include "ofMain.h"
#include "AnimationManager.h"

map<string, ofxCamera*>::iterator camerasIt;
map<string, Object3D*>::iterator objects3DIt;

Scene::Scene() {
    activeCamera = NULL;
}

Scene::~Scene() {
    activeCamera = NULL;
    activeObject = NULL;
    cameras.clear();
    lights.clear();
    objects3D.clear();
    quadGroups.clear();
    effects.clear();
}

ofxCamera* Scene::addCamera(string id) {
    ofxCamera* camera = new ofxCamera();
    camera->setId(id);
    cameras.insert(pair<string, ofxCamera*>(id, camera));
    return camera;
}

ofxCamera* Scene::getCamera(string id) {
    return cameras[id];
}

ofxCamera* Scene::activateCamera(string id) {
    activeCamera = cameras[id];
    return activeCamera;
}

ofxCamera* Scene::getActiveCamera() {
    return activeCamera;
}

map<string, ofxCamera*> Scene::getCameras() {
    return this->cameras;
}
map<string, ofxLight*> Scene::getLights() {
    return this->lights;
}

ofxLight* Scene::addLight(string id) {
    ofxLight* light = new ofxLight(id);
    lights.insert(pair<string, ofxLight*>(id, light));
    return light;
}

ofxLight* Scene::getLight(string id) {
    return lights[id];
}

void Scene::setLightOn(string lightId){
    lights[lightId]->on();
}
void Scene::setLightOff(string lightId){
    lights[lightId]->off();
}
QuadGroup* Scene::addGroup(string id) {
    QuadGroup *group = new QuadGroup(id);
    quadGroups.insert(pair<string, QuadGroup*>(id, group));
    return group;
}

QuadGroup* Scene::getGroup(string id) {
    return quadGroups[id];
}

map<string, QuadGroup*> Scene::getGroups() {
    return quadGroups;
}

Object3D* Scene::addObject3D(string id, string path) {
    Object3D *obj3D = new Object3D(id, path);
    objects3D.insert(pair<string, Object3D*>(id, obj3D));
    return obj3D;
}
void Scene::setObject3D(string id,int aParam, float aValue){
    Object3D *obj3D = objects3D[id];
    obj3D->set(aParam, aValue);
}

Object3D* Scene::getObject3D(string id) {
    return objects3D[id];
}

map<string, Object3D*> Scene::getObjects3D() {
    return objects3D;
}

Object3D* Scene::activateObject(string id) {
    activeObject = objects3D[id];
    return activeObject;
}

Object3D* Scene::getActiveObject() {
    return activeObject;
}

void Scene::deActivateObject() {
    activeObject = NULL;
}

Effect* Scene::addEffect(string id, Effect* effect) {
    effects.insert(pair<string, Effect*>(id, effect));
    return effect;
}

map<string, Effect*> Scene::getEffects() {
    return effects;
}

void Scene::testEffect(string id) {
    effects[id]->test();
}

void Scene::update() {
    AnimationManager::Update();
    TextureManager::Update();
}

void Scene::draw() {

    if(activeCamera == NULL) {
        ofLog(OF_LOG_VERBOSE, "There is no active camera.");
        return;
    }
    activeCamera->place();

	ofxLightsOn(); //turn lights on
	ofSetColor(255, 255, 255);

    map<string, ofxCamera*> camerasMap = this->cameras;
    for(camerasIt = camerasMap.begin(); camerasIt != camerasMap.end(); camerasIt++) {
        if (camerasIt->second != activeCamera)
            camerasIt->second->drawCamera();
    }

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        objects3DIt->second->draw();
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    ofxLightsOff(); //turn lights off to draw text

    activeCamera->remove();

    //Draw the 2d layers after removing the camera.

    glDisable(GL_DEPTH_TEST);
    activeCamera->drawLayers();
    glEnable(GL_DEPTH_TEST);
}

void Scene::setBackground(float r, float g, float b) {
    ofBackground(r * 255, g * 255, b * 255);
    bgColor = ofVec3f(r, g, b);
}

SerializedNode* Scene::Serialize() {
    SerializedNode *node = new SerializedNode("scene");
    node->addAttribute("backgroundcolor", bgColor);

    SerializedNode *camerasNode = new SerializedNode("cameras");
    for(camerasIt = cameras.begin(); camerasIt != cameras.end(); camerasIt++) {
        camerasNode->addChildNode(camerasIt->second->Serialize());
    }
    node->addChildNode(camerasNode);

    SerializedNode *lightsNode = new SerializedNode("lights");
    map<string, ofxLight*>::iterator lightsIt;
    for(lightsIt = lights.begin(); lightsIt != lights.end(); lightsIt++) {
        lightsNode->addChildNode(lightsIt->second->Serialize());
    }
    node->addChildNode(lightsNode);

    SerializedNode *groupsNode = new SerializedNode("groups");
    map<string, QuadGroup*>::iterator groupsIt;
    for(groupsIt = quadGroups.begin(); groupsIt != quadGroups.end(); groupsIt++) {
        groupsNode->addChildNode(groupsIt->second->Serialize());
    }
    node->addChildNode(groupsNode);

    SerializedNode *objects3dNode = new SerializedNode("objects3d");
    for(objects3DIt = objects3D.begin(); objects3DIt != objects3D.end(); objects3DIt++) {
        objects3dNode->addChildNode(objects3DIt->second->Serialize());
    }
    node->addChildNode(objects3dNode);

    SerializedNode *effectsNode = new SerializedNode("effects");
    map<string, Effect*>::iterator effectsIt;
    for(effectsIt = effects.begin(); effectsIt != effects.end(); effectsIt++) {
        effectsNode->addChildNode(effectsIt->second->Serialize());
    }
    node->addChildNode(effectsNode);

    return node;
}
