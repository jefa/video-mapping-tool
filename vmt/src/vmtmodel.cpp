#include "vmtmodel.h"
#include "OscUtil.h"
#include "FileUtil.h"
#include "base64.h"
#include "FadeEffect.h"
#include "TextureEffect.h"
#include "PositionEffect.h"

VmtModel::VmtModel() {
    scene = new Scene();
    oscManager = new OscManager();
    //won't do anything at construct time...
    oscManager->Init(network);

    timeManager = new TimeManager();
    keyEventsManager = new KeyEventsManager();
    midiEventsManager = new MidiEventsManager();
}

VmtModel::~VmtModel() {
    delete scene;
    delete oscManager;
}

Scene* VmtModel::getScene(){
    return this->scene;
}

void VmtModel::draw(){
    this->scene->draw();
}

void VmtModel::update(){
    this->scene->update();

    string effId = timeManager->Update();
    if(!effId.empty()) {
        testEffect(effId);
    }
}

void VmtModel::addNetNode(string nodeId, string address, int port, bool isActive, string camId){
    Node *nd = new Node();
    nd->id = nodeId;
    nd->address = address;
    nd->port = port;
    nd->isActive = isActive;
    nd->cameraId = camId;

    network.insert(pair<string, Node*>(nodeId, nd));

    //re-init OscManager
    this->oscManager->Init(this->network);
}

Node* VmtModel::getNode(string nodeId){
    return this->network[nodeId];

}
void VmtModel::setNodeAtributes(string nodeId, string address, int port, bool isActive, string camId){
    this->network[nodeId]->address = address;
    this->network[nodeId]->port = port;
    this->network[nodeId]->isActive = isActive;
    this->network[nodeId]->cameraId = camId;
}

string VmtModel::getNodeForCamera(string camId){
    map<string, Node*>::iterator iter = network.begin();
    while (iter != network.end()) {
        //printf("VmtModel.getNodeForCamera:: nodeId=%s, nodeCameraId=%s, reqCamId=%s\n", iter->first.c_str(), iter->second.cameraId.c_str(), camId.c_str());
        if (iter->second->cameraId == camId){
            return iter->first;
        }
        iter++;
    }
    //printf("VmtModel.getNodeForCamera:: Can't find node for camera %s\n", camId.c_str());
    return "";
}

void VmtModel::setBackground(float r, float g, float b){
    oscManager->SendMessageAll(OscUtil::createSetBackgroundMsg(r, g, b));
    scene->setBackground(r,g,b);
}

void VmtModel::addCamera(string id){
    oscManager->SendMessage(OscUtil::createAddCameraMsg(id), getNodeForCamera(id));
    scene->addCamera(id);
}

void VmtModel::setCameraPos(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, ofVec3f(x, y, z)), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->position(x, y, z);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setCameraPos camera %s is NULL", camId.c_str());
    }
}

void VmtModel::setCameraEye(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, ofVec3f(x, y, z)), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->eye(x, y, z);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setCameraEye camera %s is NULL", camId.c_str());
    }
}

void VmtModel::setCameraUp(string camId, float x, float y, float z){
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, ofVec3f(x, y, z)), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->up(x, y, z);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setCameraUp camera %s is NULL", camId.c_str());
    }
}

void VmtModel::activateCamera(string camId){
    oscManager->SendMessage(OscUtil::createActivateCameraMsg(camId), getNodeForCamera(camId));
    scene->activateCamera(camId);
}
void VmtModel::setPerspective(string camId, float _fov, float _aspect, float _zNear, float _zFar){
    oscManager->SendMessage(OscUtil::createSetPerspectiveMsg(camId, _fov, _aspect, _zNear, _zFar), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->perspective(_fov, _aspect, _zNear, _zFar);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setPerspective camera %s is NULL", camId.c_str());
    }
}
void VmtModel::setIsProjector(string camId, bool NewVal){
    oscManager->SendMessage(OscUtil::createSetIsProjectorMsg(camId,NewVal), getNodeForCamera(camId));;
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        camera->setIsProjector(NewVal);
    }
    else {
        ofLog(OF_LOG_ERROR, "VmtModel::setIsProjector camera %s is NULL", camId.c_str());
    }
}

ofxCamera* VmtModel::getActiveCamera(){
    return scene->getActiveCamera();
}

void VmtModel::addGroup(string groupId){
    oscManager->SendMessageAll(OscUtil::createAddGroupMsg(groupId));
    scene->addGroup(groupId);
}

QuadGroup* VmtModel::getGroup(string groupId){
    return scene->getGroup(groupId);
}

map<string, QuadGroup*> VmtModel::getGroups(){
    return scene->getGroups();
}

void VmtModel::addLayer(string camId, string layerId){
    oscManager->SendMessage(OscUtil::createAddLayerMsg(camId, layerId), getNodeForCamera(camId));
    if (scene->getCamera(camId) != NULL)
        scene->getCamera(camId)->addLayer2D(layerId);
}

void VmtModel::addQuad(string camId, string layerId, string quadId){
    oscManager->SendMessage(OscUtil::createAddQuadMsg(camId, layerId, quadId), getNodeForCamera(camId));
    if (scene->getCamera(camId) != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera->getLayer2D(layerId) != NULL)
            camera->getLayer2D(layerId)->addQuad2D(quadId);
    }
}

void VmtModel::addQuadToGroup(string groupId, string camId, string layerId, string quadId){
    oscManager->SendMessage(OscUtil::createAddQuadToGroupMsg(groupId, camId, layerId, quadId), getNodeForCamera(camId));
    QuadGroup *group = scene->getGroup(groupId);
    if (group != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera != NULL) {
            Layer2D *layer = camera->getLayer2D(layerId);
            if (layer != NULL){
                Quad2D *quad = layer->getQuad2D(quadId);
                if (quad != NULL)
                    group->addQuad2D(quad);
            }
        }
    }
}

void VmtModel::enableQuad(string camId, string layerId, string quadId, bool enabled){
    oscManager->SendMessage(OscUtil::createEnableQuadMsg(camId, layerId, quadId, enabled), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            Quad2D *quad = layer->getQuad2D(quadId);
            if (quad != NULL)
                quad->setEnabled(enabled);
        }
    }
}

void VmtModel::enableLayer(string camId, string layerId, bool enabled){
    oscManager->SendMessage(OscUtil::createEnableLayerMsg(camId, layerId, enabled), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            layer->setEnabled(enabled);
        }
    }
}


void VmtModel::setQuadPoint(string camId, string layerId, string quadId,
            int point, float coordX, float coordY){
    oscManager->SendMessage(OscUtil::createSetQuadPointMsg(camId, layerId, quadId, point, coordX, coordY), getNodeForCamera(camId));
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            Quad2D *quad = layer->getQuad2D(quadId);
            if (quad != NULL)
                quad->setPoint(point, coordX, coordY);
        }
    }
}

void VmtModel::setActiveCamDisplayHelpers(bool display) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetActiveCamDisplayHelpersMsg(display), getNodeForCamera(camId));

    cam->setDisplayHelpers(display);
}

ofVec2f VmtModel::getActiveCamHelperCoord(bool isSrc, int i) {
    //No manda mensaje por ser getter
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return ofVec2f(0,0);

    if(isSrc)
        return cam->getSrcHelperCoord(i);
    else
        return cam->getDstHelperCoord(i);
}

void VmtModel::setActiveCamHelperCoord(bool isSrc, int i, ofVec2f coord) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetActiveCamHelperCoordMsg(isSrc,i,coord), getNodeForCamera(camId));

    if(isSrc)
        cam->setSrcHelperCoord(i, coord);
    else
        cam->setDstHelperCoord(i, coord);
}

void VmtModel::calibrateActiveCam() {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createCalibrateMsg(), getNodeForCamera(camId));

    cam->calculateHomography();
}

void VmtModel::resetActiveCamCalibraton() {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createResetCalibrationMsg(), getNodeForCamera(camId));

    cam->resetHomography();
}

void VmtModel::addObject3D(string objId, string path){

/*    FILE * pFile;
    long lSize;
    size_t result;

    pFile = fopen ( path.c_str() , "rb" );
    if (pFile==NULL) {
        fputs ("File error",stderr);
        return;
    }

    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    char* buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {
        fputs ("Memory error",stderr);
        return ;
    }

    result = fread (buffer, 1, lSize, pFile);
    if (result != lSize) {
        fputs ("Reading error",stderr);
        return ;
    }

    fclose (pFile);

    string base64strEncoded = base64_encode((unsigned char*)buffer , lSize);
*/
    oscManager->SendMessageAll(OscUtil::createAddObject3dMsg(objId, path /*base64strEncoded*/));
    scene->addObject3D(objId, path);
}

Object3D* VmtModel::getObject3D(string objId){
    return scene->getObject3D(objId);
}
void VmtModel::setObject3D(string objId, int aParam, float aValue){
    if (scene->getObject3D(objId) == NULL){
        printf("VmtModel::setObject3D: object does not exists(%s)\n", objId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createSetObject3DPosMsg(objId, aParam, aValue));
    scene->setObject3D(objId, aParam, aValue);
}

Layer2D* VmtModel::getLayer2D(string layId){
    return scene->getActiveCamera()->getLayer2D(layId);
}

ofxLight* VmtModel::getLight(string lightId){
    return scene->getLight(lightId);
}
void VmtModel::setLightOn(string lightId){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightOn: object does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createSetOnLightMsg(lightId));

    scene->setLightOn(lightId);
}
void VmtModel::setLightOff(string lightId){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightOff: object does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createSetOffLightMsg(lightId));
    scene->setLightOff(lightId);
}

void VmtModel::addPositionEffect(string effectId, string objId, ofVec3f posIni, ofVec3f posFin, float delay){
    if (scene->getObject3D(objId) == NULL){
        printf("VmtModel::addPositionEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddPositionEffectMsg(effectId, objId, posIni, posFin, delay));
    scene->addEffect(effectId, new PositionEffect(effectId, scene->getObject3D(objId), posIni, posFin, delay));
}

void VmtModel::addFadeEffect(string effectId, string groupId, ofVec4f colorIni, ofVec4f colorFin, float delay){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtModel::addFadeEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddFadeEffectMsg(effectId, groupId, colorIni, colorFin, delay));
    scene->addEffect(effectId, new FadeEffect(effectId, scene->getGroup(groupId), colorIni, colorFin, delay));
}

void VmtModel::addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtModel::addTextureGroupEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddTextureGroupEffectMsg(effectId, groupId, texturePath, type));
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getGroup(groupId), texturePath, type));
}

void VmtModel::addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type) {
    if (scene->getObject3D(objId) == NULL){
        printf("VmtModel::addTextureObjectEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createAddTextureObjectEffectMsg(effectId, objId, facesId, texturePath, type));
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getObject3D(objId), facesId, texturePath, type));
}

void VmtModel::testEffect(string id){
    oscManager->SendMessageAll(OscUtil::createTestEffectMsg(id));
    this->scene->testEffect(id);
}

void VmtModel::addLight(string lightId){
    oscManager->SendMessageAll(OscUtil::createAddLightMsg(lightId));
    scene->addLight(lightId);
}

void VmtModel::setLightSpecular(string lightId, float r, float g, float b){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightSpecularMsg(lightId, r, g, b));
    scene->getLight(lightId)->specular(r, g, b);
}

void VmtModel::setLightDirectional(string lightId, float r, float g, float b,
                                   float nx, float ny, float nz){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightDirectionalMsg(lightId, r, g, b, nx, ny, nz));
    scene->getLight(lightId)->directionalLight(r, g, b, nx, ny, nz);
}

void VmtModel::setLightSpot(string lightId, float r, float g, float b,
                                   float x, float y, float z,
                                   float nx, float ny, float nz,
                                   float angle, float concentration){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightSpotMsg(lightId, r, g, b, x, y, z, nx, ny, nz, angle, concentration));
    scene->getLight(lightId)->spotLight(r, g, b, x, y, z, nx, ny, nz, angle, concentration);
}

void VmtModel::setLightPoint(string lightId, float r, float g, float b,
                                   float x, float y, float z){
    if (scene->getLight(lightId) == NULL){
        printf("VmtModel::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    oscManager->SendMessageAll(OscUtil::createLightPointMsg(lightId, r, g, b, x, y, z));
    scene->getLight(lightId)->pointLight(r, g, b, x, y, z);
}

void VmtModel::setClientResolution(string camId, int resx, int resy) {
    //Esta operacion no manda mensajes porque es solo del editor.
    ofxCamera *cam = scene->getCamera(camId);
    cam->setClientResolution(resx, resy);
}

void VmtModel::setControlMode(CAM_CONTROL_MODE mode) {
    //Esta operacion no manda mensajes porque es solo del editor.
    control_mode = mode;
}

CAM_CONTROL_MODE VmtModel::getControlMode() {
    return control_mode;
}

void VmtModel::OrbitActiveCamera(int dx, int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float angleX = -dx * 0.5f;
    float angleY = dy * 0.5f;

    cam->orbitAround(cam->getEye(), ofVec3f(0,1,0), angleX);

    ofVec3f dir = -(cam->getDir());
    ofVec3f axis2 = dir.getCrossed(ofVec3f(0,1,0));
    axis2.normalize();

    cam->orbitAround(cam->getEye(), axis2, angleY);

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, cam->getPosition()), getNodeForCamera(camId));
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, cam->getEye()), getNodeForCamera(camId));
}

void VmtModel::RollActiveCamera(int dx) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float angleX = -dx * 0.5f;

    ofVec3f dir = -(cam->getDir());
    ofVec3f up = cam->getUp();
    up.rotate(angleX, dir);
    cam->up(up);

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetCameraUpMsg(camId, cam->getUp()), getNodeForCamera(camId));
}

void VmtModel::DollyActiveCamera(int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float delta = dy * 0.5f;

    ofVec3f dir = -(cam->getDir());
    dir.normalize();

    ofVec3f pos = cam->getPosition();
    pos += dir * dy;

    cam->position(pos);

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, cam->getPosition()), getNodeForCamera(camId));
}

void VmtModel::PanActiveCamera(int dx, int dy) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    float moveX = -dx * 0.25f;
    float moveY = dy * 0.25f;

    ofVec3f dir = -(cam->getDir());
    dir.normalize();
    ofVec3f up = cam->getUp();
    up.normalize();
    ofVec3f left = up.crossed(dir);
    ofVec3f move = left * moveX + up * moveY;

    cam->moveGlobal(move);

    string camId = cam->getId();
    oscManager->SendMessage(OscUtil::createSetCameraPosMsg(camId, cam->getPosition()), getNodeForCamera(camId));
    oscManager->SendMessage(OscUtil::createSetCameraEyeMsg(camId, cam->getEye()), getNodeForCamera(camId));
}

void addXMLNode(ofxXmlSettings &xml, SerializedNode* node) {
    int tagI = xml.addTag(node->getTagId());

    vector<pair<string, string> > attributes = node->getAttributes();
    vector<pair<string, string> >::iterator attributesIt;
    for(attributesIt = attributes.begin(); attributesIt != attributes.end(); attributesIt++) {
        xml.addAttribute(node->getTagId(), attributesIt->first, attributesIt->second, tagI);
    }

    xml.pushTag(node->getTagId(), tagI);

    vector<SerializedNode*> childNodes = node->getChildNodes();
    vector<SerializedNode*>::iterator childNodesIt;
    for(childNodesIt = childNodes.begin(); childNodesIt != childNodes.end(); childNodesIt++) {
        addXMLNode(xml, *childNodesIt);
    }
    xml.popTag();
}

void VmtModel::saveShow(string filepath) {
    showXML.clear();

    showXML.addTag("vmtshow");
    showXML.addAttribute("vmtshow", "name", "showname1", 0);

    showXML.pushTag("vmtshow", 0);

    SerializedNode* networkNode = this->SerializeNetwork();
    addXMLNode(showXML, networkNode);

    SerializedNode* sceneNode = scene->Serialize();
    addXMLNode(showXML, sceneNode);

    SerializedNode* timedEventsNode = timeManager->Serialize();
    addXMLNode(showXML, timedEventsNode);

    SerializedNode* keyEventsNode = keyEventsManager->Serialize();
    addXMLNode(showXML, keyEventsNode);

    showXML.popTag();//vmtshow

    showXML.saveFile(filepath);
}

SerializedNode* VmtModel::SerializeNetwork() {
    SerializedNode *node = new SerializedNode("network");

    map<string, Node*>::iterator networkIt;
    for(networkIt = network.begin(); networkIt != network.end(); networkIt++) {
        SerializedNode *networkNode = new SerializedNode("node");
        networkNode->addAttribute("id", networkIt->first);
        networkNode->addAttribute("address", networkIt->second->address);
        networkNode->addAttribute("port", networkIt->second->port);
        networkNode->addAttribute("isActive", networkIt->second->isActive);
        networkNode->addAttribute("cameraId", networkIt->second->cameraId);
        node->addChildNode(networkNode);
    }

    return node;
}

ofVec2f parseVector2f(string str) {
    std::stringstream sstr(str);
    float x, y;
    sstr >> x >> y;
    return ofVec2f(x,y);
}

ofVec3f parseVector3f(string str) {
    std::stringstream sstr(str);
    float x,y,z;
    sstr >> x >> y >> z;
    return ofVec3f(x,y,z);
}

ofVec4f parseVector4f(string str) {
    std::stringstream sstr(str);
    float x,y,z,w;
    sstr >> x >> y >> z >> w;
    return ofVec4f(x,y,z,w);
}

float parseFloat(string str) {
    std::stringstream sstr(str);
    float x;
    sstr >> x;
    return x;
}

int parseInt(string str) {
    std::stringstream sstr(str);
    int x;
    sstr >> x;
    return x;
}

bool parseBool(string str) {
    return str.compare("true") == 0;
}

void VmtModel::loadShow(string filepath) {

    map<string, string> quadsByLayer;
    map<string, string> quadsByCamera;

    showXML.loadFile(filepath);

    showXML.pushTag("vmtshow");

    showXML.pushTag("network");
    for(int nodeI = 0; nodeI < showXML.getNumTags("node"); nodeI++) {
        string nodeId = showXML.getAttribute("node", "id", "", nodeI);
        string address = showXML.getAttribute("node", "address", "localhost", nodeI);
        int port = parseInt(showXML.getAttribute("node", "port", "54321", nodeI));
        bool isActive = parseBool(showXML.getAttribute("node", "isActive", "true", nodeI));
        string camId = showXML.getAttribute("node", "cameraId", "", nodeI);
        this->addNetNode(nodeId, address, port, isActive, camId);
    }
    showXML.popTag();//network

        ofVec3f bgColor = parseVector3f(showXML.getAttribute("scene", "backgroundcolor", "0 0 0", 0));
        this->setBackground(bgColor.x, bgColor.y, bgColor.y);

    showXML.pushTag("scene");

    showXML.pushTag("cameras");
        for(int camI = 0; camI < showXML.getNumTags("camera"); camI++) {
            string camId = showXML.getAttribute("camera", "id", "", camI);
            this->addCamera(camId);
            this->activateCamera(camId);

            showXML.pushTag("camera", camI);

                ofVec3f camPos = parseVector3f(showXML.getAttribute("view", "pos", "0 0 0", 0));
                this->setCameraPos(camId, camPos.x, camPos.y, camPos.z);

                ofVec3f camEye = parseVector3f(showXML.getAttribute("view", "eye", "0 0 0", 0));
                this->setCameraEye(camId, camEye.x, camEye.y, camEye.z);

                int clientResX = parseInt(showXML.getAttribute("projection", "resx", "800", 0));
                int clientResY = parseInt(showXML.getAttribute("projection", "resy", "600", 0));

                this->setClientResolution(camId, clientResX, clientResY);

                showXML.pushTag("layers", 0);
                for(int layerI = 0; layerI < showXML.getNumTags("layer"); layerI++) {
                    string layerId = showXML.getAttribute("layer", "id", "", layerI);
                    this->addLayer(camId, layerId);
                    showXML.pushTag("layer", layerI);
                    for(int quadI = 0; quadI < showXML.getNumTags("quad"); quadI++) {
                        string quadId = showXML.getAttribute("quad", "id", "", quadI);

                        quadsByCamera.insert(pair<string, string>(quadId, camId));
                        quadsByLayer.insert(pair<string, string>(quadId, layerId));

                        bool quadEnabled = parseBool(showXML.getAttribute("quad", "enabled", "true", quadI));
                        ofVec2f quadP0 = parseVector2f(showXML.getAttribute("quad", "p0", "0 0", quadI));
                        ofVec2f quadP1 = parseVector2f(showXML.getAttribute("quad", "p1", "0 1", quadI));
                        ofVec2f quadP2 = parseVector2f(showXML.getAttribute("quad", "p2", "1 1", quadI));
                        ofVec2f quadP3 = parseVector2f(showXML.getAttribute("quad", "p3", "1 0", quadI));
                        this->addQuad(camId, layerId, quadId);
                        this->enableQuad(camId, layerId, quadId, quadEnabled);
                        this->setQuadPoint(camId, layerId, quadId, 0, quadP0.x, quadP0.y);
                        this->setQuadPoint(camId, layerId, quadId, 1, quadP1.x, quadP1.y);
                        this->setQuadPoint(camId, layerId, quadId, 2, quadP2.x, quadP2.y);
                        this->setQuadPoint(camId, layerId, quadId, 3, quadP3.x, quadP3.y);
                    }
                    showXML.popTag();//layer
                }
                showXML.popTag();//layers
            showXML.popTag();//camera
        }
    showXML.popTag();//cameras

    showXML.pushTag("lights");
    for(int lightI = 0; lightI < showXML.getNumTags("light"); lightI++) {
        string lightId = showXML.getAttribute("light", "id", "", lightI);
        ofVec3f specularVec = parseVector3f(showXML.getAttribute("light", "specular", "255 255 255", lightI));
        ofVec3f diffuseVec = parseVector3f(showXML.getAttribute("light", "diffuse", "255 255 255", lightI));
        ofVec3f directionVec = parseVector3f(showXML.getAttribute("light", "direction", "0 -1 0", lightI));

        this->addLight(lightId);
        this->setLightSpecular(lightId, specularVec.x, specularVec.y, specularVec.z);
        this->setLightDirectional(lightId, diffuseVec.x, diffuseVec.y, diffuseVec.z, directionVec.x, directionVec.y, directionVec.z);
    }
    showXML.popTag();//lights

    showXML.pushTag("groups");
    for(int groupI = 0; groupI < showXML.getNumTags("group"); groupI++) {
        string groupId = showXML.getAttribute("group", "id", "", groupI);
        this->addGroup(groupId);
        showXML.pushTag("group", groupI);
        for(int quadI = 0; quadI < showXML.getNumTags("quad"); quadI++) {
            string quadId = showXML.getAttribute("quad", "id", "", quadI);
            string camId = quadsByCamera[quadId];
            string layerId = quadsByLayer[quadId];
            this->addQuadToGroup(groupId, camId, layerId, quadId);
        }
        showXML.popTag();//group
    }
    showXML.popTag();//groups

    showXML.pushTag("objects3d");
    for(int object3dI = 0; object3dI < showXML.getNumTags("object3d") ; object3dI++) {
        string object3dId = showXML.getAttribute("object3d", "id", "", object3dI);
        string obj3dfilename = showXML.getAttribute("object3d", "filename", "", object3dI);
        ofVec3f obj3dPos = parseVector3f(showXML.getAttribute("object3d", "pos", "", object3dI));
        ofVec3f obj3dScale = parseVector3f(showXML.getAttribute("object3d", "scale", "", object3dI));
        this->addObject3D(object3dId, obj3dfilename);
    }
    showXML.popTag();//objects3d;

    showXML.pushTag("effects");
    for(int effectI = 0; effectI < showXML.getNumTags("effect"); effectI++) {
        string effectId = showXML.getAttribute("effect", "id", "", effectI);
        string effectType = showXML.getAttribute("effect", "type", "", effectI);

        if(effectType.compare("position") == 0) {
            string objId = showXML.getAttribute("effect", "objid", "", effectI);
            ofVec3f pos1 = parseVector3f(showXML.getAttribute("effect", "pos1", "0 0 0", effectI));
            ofVec3f pos2 = parseVector3f(showXML.getAttribute("effect", "pos2", "0 0 0", effectI));
            float delay = parseFloat(showXML.getAttribute("effect", "delay", "0", effectI));
            this->addPositionEffect(effectId, objId, pos1, pos2, delay);
        }
        else if(effectType.compare("fade") == 0) {
            string groupId = showXML.getAttribute("effect", "groupid", "", effectI);
            ofVec4f col1 = parseVector4f(showXML.getAttribute("effect", "col1", "1 1 1 1", effectI));
            ofVec4f col2 = parseVector4f(showXML.getAttribute("effect", "col2", "1 1 1 1", effectI));
            float delay = parseFloat(showXML.getAttribute("effect", "delay", "0", effectI));
            this->addFadeEffect(effectId, groupId, col1, col2, delay);
        }
        else if(effectType.compare("grouptexture") == 0) {
            string groupId = showXML.getAttribute("effect", "groupid", "", effectI);
            string textureName = showXML.getAttribute("effect", "texturename", "", effectI);

            string textureType = showXML.getAttribute("effect", "texturetype", "VIDEO_TEXTURE", effectI);
            if(textureType.compare("VIDEO_TEXTURE") == 0) {
                this->addTextureGroupEffect(effectId, groupId, textureName, VIDEO_TEXTURE);
            }
            else {
                this->addTextureGroupEffect(effectId, groupId, textureName, IMAGE_TEXTURE);
            }
        }
        else if(effectType.compare("object3dtexture") == 0) {
            string objId = showXML.getAttribute("effect", "objid", "", effectI);
            string textureName = showXML.getAttribute("effect", "texturename", "", effectI);
            string facesid = showXML.getAttribute("effect", "facesid", "", effectI);
            string textureType = showXML.getAttribute("effect", "texturetype", "VIDEO_TEXTURE", effectI);

            if(textureType.compare("VIDEO_TEXTURE") == 0) {
                this->addTextureObjectEffect(effectId, objId, facesid, textureName, VIDEO_TEXTURE);
            }
            else {
                this->addTextureObjectEffect(effectId, objId, facesid, textureName, IMAGE_TEXTURE);
            }
            //TODO: Deshardcodear VIDEO_TEXTURE
        }
    }
    showXML.popTag();//effects
    showXML.popTag();//scene

    showXML.pushTag("timedevents");
    for(int eventI = 0; eventI < showXML.getNumTags("timedevent"); eventI++) {
        float eventTime = parseFloat(showXML.getAttribute("timedevent", "t", "0", eventI));
        string effectId = showXML.getAttribute("timedevent", "effect", "", eventI);
        this->scheduleEvent(eventTime, effectId);
    }
    showXML.popTag();//timedevents

    showXML.pushTag("keyevents");
    for(int eventI = 0; eventI < showXML.getNumTags("keyevent"); eventI++) {
        int eventKey = parseInt(showXML.getAttribute("keyevent", "key", "0", eventI));
        string effectId = showXML.getAttribute("keyevent", "effect", "", eventI);
        this->addKeyEvent(eventKey, effectId);
    }
    showXML.popTag();//keyevents

    showXML.popTag();//vmtshow
}

void VmtModel::resetScene() {
    oscManager->SendMessageAll(OscUtil::createResetSceneMsg());
    delete this->scene;
}

map<string, Node*> VmtModel::getNodes() {
    return this->network;
}
map<string, ofxCamera*> VmtModel::getCameras() {
    return this->scene->getCameras();
}

map<string, Object3D*> VmtModel::getObjects3D() {
    return this->scene->getObjects3D();
}

map<string, Effect*> VmtModel::getEffects() {
    return this->scene->getEffects();
}
map<float, string> VmtModel::getEvtEffects() {
    return timeManager->getScheduleEvents();
}
map<char, string> VmtModel::getKeyEffects() {
    return keyEventsManager->getKeyEvents();
}
map<ofxMidiEventArgs*, string> VmtModel::getMidiEffects() {
    return midiEventsManager->getMidiEvents();
}
void VmtModel::scheduleEvent(float time, string effectId) {
    timeManager->ScheduleEvent(time, effectId);
}
void VmtModel::removeTimeEvent(float time, string effectId) {
    timeManager->removeTimeEvent(time, effectId);
}
void VmtModel::addKeyEvent(char keyId, string effectId) {
    keyEventsManager->addKeyEvent(keyId, effectId);
}
void VmtModel::removeKeyEvent(char keyId, string effectId) {
    keyEventsManager->removeKeyEvent(keyId, effectId);
}
bool VmtModel::hasKeyEvent(char keyId) {
    return keyEventsManager->hasKeyEvent(keyId);
}

string VmtModel::getEffectIdForKeyEvent(char keyId) {
    return keyEventsManager->getEffectId(keyId);
}
bool VmtModel::hasMidiEvent(ofxMidiEventArgs* MidiMsg) {
    return midiEventsManager->hasMidiEvent(MidiMsg);
}
void VmtModel::addMidiEvent(ofxMidiEventArgs * MidiMsg, string effectId) {
    midiEventsManager->addMidiEvent(MidiMsg, effectId);
}
void VmtModel::removeMidiEvent(ofxMidiEventArgs * MidiMsg, string effectId) {
    midiEventsManager->removeMidiEvent(MidiMsg, effectId);
}
string VmtModel::getEffectIdForMidiEvent(ofxMidiEventArgs * MidiMsg) {
    return midiEventsManager->getEffectId(MidiMsg);
}
void VmtModel::startTimeManager(TIMER_MODE mode) {
    timeManager->Start(mode);
}

double VmtModel::getTotalTime(){
    return timeManager->getTotalTime();
}
