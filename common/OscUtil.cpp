#include "OscUtil.h"
#include "FileUtil.h"
#include "base64.h"

#include "FadeEffect.h"
#include "PositionEffect.h"
#include "TextureEffect.h"

OscUtil::OscUtil()
{
    //ctor
}

OscUtil::~OscUtil()
{
    //dtor
}

ofxOscMessage OscUtil::createResetSceneMsg() {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(SCENE_RESET);
    return oscMessage;
}

void OscUtil::processResetSceneMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    sceneHandler->resetScene();
}

ofxOscMessage OscUtil::createSetBackgroundMsg(float r, float g, float b){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(SCENE_BACKGROUND_ADDR);
    oscMessage.addFloatArg(r);
    oscMessage.addFloatArg(g);
    oscMessage.addFloatArg(b);
    return oscMessage;
}

void OscUtil::processSetBackgroundMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    int r = msg.getArgAsFloat(0);
    int g = msg.getArgAsFloat(1);
    int b = msg.getArgAsFloat(2);
    sceneHandler->setBackground(r,g,b);
}

ofxOscMessage OscUtil::createAddCameraMsg(string id)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_ADD_ADDR);
    oscMessage.addStringArg(id);
    return oscMessage;
}

void OscUtil::processAddCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    sceneHandler->addCamera(id);
}

ofxOscMessage OscUtil::createSetCameraPosMsg(string id, ofVec3f position)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SETPOS_ADDR);
    oscMessage.addStringArg(id);
    oscMessage.addFloatArg(position[0]);
    oscMessage.addFloatArg(position[1]);
    oscMessage.addFloatArg(position[2]);
    return oscMessage;
}

void OscUtil::processSetCameraPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    float x = msg.getArgAsFloat(1);
    float y = msg.getArgAsFloat(2);
    float z = msg.getArgAsFloat(3);
    sceneHandler->setCameraPos(id, x, y, z);
}

ofxOscMessage OscUtil::createSetCameraEyeMsg(string id, ofVec3f eye)
{
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SETEYE_ADDR);
    oscMessage.addStringArg(id);
    oscMessage.addFloatArg(eye[0]);
    oscMessage.addFloatArg(eye[1]);
    oscMessage.addFloatArg(eye[2]);
    return oscMessage;
}

void OscUtil::processSetCameraEyeMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string id = msg.getArgAsString(0);
    float x = msg.getArgAsFloat(1);
    float y = msg.getArgAsFloat(2);
    float z = msg.getArgAsFloat(3);
    sceneHandler->setCameraEye(id, x, y, z);
}

ofxOscMessage OscUtil::createSetCameraUpMsg(string id, ofVec3f up) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SETUP_ADDR);
    oscMessage.addStringArg(id);
    oscMessage.addFloatArg(up[0]);
    oscMessage.addFloatArg(up[1]);
    oscMessage.addFloatArg(up[2]);
    return oscMessage;
}

void OscUtil::processSetCameraUpMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string id = msg.getArgAsString(0);
    float x = msg.getArgAsFloat(1);
    float y = msg.getArgAsFloat(2);
    float z = msg.getArgAsFloat(3);
    sceneHandler->setCameraUp(id, x, y, z);
}

ofxOscMessage OscUtil::createActivateCameraMsg(string id){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_ACTIVATE_ADDR);
    oscMessage.addStringArg(id);
    return oscMessage;
}

void OscUtil::processActivateCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    sceneHandler->activateCamera(camId);
}

ofxOscMessage OscUtil::createAddQuadMsg(string camId, string layerId, string quadId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(QUAD_ADD_ADDR);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    return oscMessage;
}

void OscUtil::processAddQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    sceneHandler->addQuad(camId, layerId, quadId);
}

ofxOscMessage OscUtil::createSetQuadPointMsg(string camId, string layerId, string quadId,
                                           int point, float coordX, float coordY){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(QUAD_SETPOINT_ADDR);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    oscMessage.addIntArg(point);
    oscMessage.addFloatArg(coordX);
    oscMessage.addFloatArg(coordY);
    return oscMessage;
}

void OscUtil::processSetQuadPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    int point = msg.getArgAsInt32(3);
    float coordX = msg.getArgAsFloat(4);
    float coordY = msg.getArgAsFloat(5);
    sceneHandler->setQuadPoint(camId, layerId, quadId, point, coordX, coordY);
}

ofxOscMessage OscUtil::createEnableQuadMsg(string camId, string layerId, string quadId, bool enabled){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(QUAD_ENABLE_ADDR);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    oscMessage.addIntArg(enabled);
    return oscMessage;
}



void OscUtil::processEnableQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    string quadId = msg.getArgAsString(2);
    bool enabled = msg.getArgAsInt32(3);
    sceneHandler->enableQuad(camId, layerId, quadId, enabled);
}

ofxOscMessage OscUtil::createAddLayerMsg(string camId, string layerId) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LAYER_ADD_ADDR);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    return oscMessage;
}

void OscUtil::processAddLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    sceneHandler->addLayer(camId, layerId);
}

ofxOscMessage OscUtil::createEnableLayerMsg(string camId, string layerId, bool enabled){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LAYER_ENABLE_ADDR);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addIntArg(enabled);
    return oscMessage;
}

void OscUtil::processEnableLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string camId = msg.getArgAsString(0);
    string layerId = msg.getArgAsString(1);
    bool enabled = msg.getArgAsInt32(2);
    sceneHandler->enableLayer(camId, layerId, enabled);
}

ofxOscMessage OscUtil::createAddGroupMsg(string groupId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(GROUP_ADD_ADDR);
    oscMessage.addStringArg(groupId);
    return oscMessage;
}

void OscUtil::processAddGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string groupId = msg.getArgAsString(0);
    sceneHandler->addGroup(groupId);
}

ofxOscMessage OscUtil::createAddQuadToGroupMsg(string groupId, string camId, string layerId, string quadId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(GROUP_ADDQUAD_ADDR);
    oscMessage.addStringArg(groupId);
    oscMessage.addStringArg(camId);
    oscMessage.addStringArg(layerId);
    oscMessage.addStringArg(quadId);
    return oscMessage;
}

void OscUtil::processAddQuadToGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string groupId = msg.getArgAsString(0);
    string camId = msg.getArgAsString(1);
    string layerId = msg.getArgAsString(2);
    string quadId = msg.getArgAsString(3);
    sceneHandler->addQuadToGroup(groupId, camId, layerId, quadId);
}

ofxOscMessage OscUtil::createAddObject3dMsg(string objId, string base64data){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(OBJECT_ADD_ADDR);
    oscMessage.addStringArg(objId);
    oscMessage.addStringArg(base64data);

/*    cout << "\tbase64data.size==== " << base64data.size() << endl;

    int chunks = base64data.size() / 2000;
    int rest = base64data.size() % 2000;
    oscMessage.addIntArg(chunks);
    for (int i=0; i<(chunks-1); i++){
        cout << "\tchunk: " << i << " de " << chunks << endl;
        cout << "\tpos: " << i*2000 << endl;
        //if ( i = (chunks-1))
            //oscMessage.addStringArg(base64data.substr(i * 2000, rest));
        //else
            oscMessage.addStringArg(base64data.substr(i * 2000, 2000));
    }
    oscMessage.addStringArg(base64data.substr((chunks-1) * 2000, rest));

    /try {
        oscMessage.addStringArg(base64data.substr(0,3000));
    } catch (exception& e)
    {
        cout << "\tEXCEPCIONNNNN!!!!! " << e.what() << endl;
    }*/
    return oscMessage;
}

void OscUtil::processAddObject3dMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string objId = msg.getArgAsString(0);
    string path = msg.getArgAsString(1);
    /*int chunks = msg.getArgAsInt32(1);
    string base64data;
    for (int i=0; i<chunks; i++){
        base64data += msg.getArgAsString(i+2);
    }
    printf("\tBASE64.DATA=%s\n", base64data.c_str());

    string path = "data/transferred/" + objId + ".3ds";

    string base64strDecoded = base64_decode(base64data);

    bool saved = FileUtil::writeBinaryFile(path, base64strDecoded);
*/
    sceneHandler->addObject3D(objId, path);
}

ofxOscMessage OscUtil::createSetObject3DPosMsg(string objId, int aParam, float aValue){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(OBJECT_SET_POS);
    oscMessage.addStringArg(objId);
    oscMessage.addIntArg(aParam);
    oscMessage.addFloatArg(aValue);
    return oscMessage;
}

void OscUtil::processSetObject3DPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string objId = msg.getArgAsString(0);
    int pos = msg.getArgAsInt32(1);
    float value = msg.getArgAsFloat(2);
    sceneHandler->setObject3D(objId, pos, value);
}

ofxOscMessage OscUtil::createAddPositionEffectMsg(string effectId, string objId, ofVec3f posIni,
                                                ofVec3f posFin, float delay){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(EFFECT_ADD_POSITION_ADDR);
    oscMessage.addStringArg(effectId);
    oscMessage.addStringArg(objId);
    oscMessage.addFloatArg(posIni[0]);
    oscMessage.addFloatArg(posIni[1]);
    oscMessage.addFloatArg(posIni[2]);
    oscMessage.addFloatArg(posFin[0]);
    oscMessage.addFloatArg(posFin[1]);
    oscMessage.addFloatArg(posFin[2]);
    oscMessage.addFloatArg(delay);
    return oscMessage;
}

void OscUtil::processAddPositionEffectMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string effId = m.getArgAsString(0);
    string objId = m.getArgAsString(1);
    float posIniX = m.getArgAsFloat(2);
    float posIniY = m.getArgAsFloat(3);
    float posIniZ = m.getArgAsFloat(4);
    float posFinX = m.getArgAsFloat(5);
    float posFinY = m.getArgAsFloat(6);
    float posFinZ = m.getArgAsFloat(7);
    float delay = m.getArgAsFloat(8);
    sceneHandler->addPositionEffect(effId, objId, ofVec3f(posIniX,posIniY,posIniZ),
                                    ofVec3f(posFinX,posFinY,posFinZ), delay);
}

ofxOscMessage OscUtil::createAddFadeEffectMsg(string effectId, string groupId, ofVec4f colorIni,
                                            ofVec4f colorFin, float delay){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(EFFECT_ADD_FADE_ADDR);
    oscMessage.addStringArg(effectId);
    oscMessage.addStringArg(groupId);
    oscMessage.addFloatArg(colorIni[0]);
    oscMessage.addFloatArg(colorIni[1]);
    oscMessage.addFloatArg(colorIni[2]);
    oscMessage.addFloatArg(colorIni[3]);
    oscMessage.addFloatArg(colorFin[0]);
    oscMessage.addFloatArg(colorFin[1]);
    oscMessage.addFloatArg(colorFin[2]);
    oscMessage.addFloatArg(colorFin[3]);
    oscMessage.addFloatArg(delay);
    return oscMessage;
}

void OscUtil::processAddFadeEffectMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string effId = m.getArgAsString(0);
    string groupId = m.getArgAsString(1);
    float colIniR = m.getArgAsFloat(2);
    float colIniG = m.getArgAsFloat(3);
    float colIniB = m.getArgAsFloat(4);
    float colIniA = m.getArgAsFloat(5);
    float colFinR = m.getArgAsFloat(6);
    float colFinG = m.getArgAsFloat(7);
    float colFinB = m.getArgAsFloat(8);
    float colFinA = m.getArgAsFloat(9);
    float delay = m.getArgAsFloat(10);
    sceneHandler->addFadeEffect(effId, groupId, ofVec4f(colIniR,colIniG,colIniB,colIniA),
                     ofVec4f(colFinR,colFinG,colFinB,colFinA), delay);
}

ofxOscMessage OscUtil::createAddTextureGroupEffectMsg(string effectId, string groupId, string texturePath, textureType type) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(EFFECT_ADD_TEXTURE_GROUP_ADDR);
    oscMessage.addStringArg(effectId);
    oscMessage.addStringArg(groupId);
    oscMessage.addStringArg(texturePath);
    oscMessage.addIntArg(type);
    return oscMessage;
}

void OscUtil::processAddTextureGroupEffectMsg(ofxOscMessage m, ISceneHandler *sceneHandler) {
    string effId = m.getArgAsString(0);
    string groupId = m.getArgAsString(1);
    string texturePath = m.getArgAsString(2);
    textureType type = (textureType)(m.getArgAsInt32(3));
    sceneHandler->addTextureGroupEffect(effId, groupId, texturePath, type);
}

ofxOscMessage OscUtil::createAddTextureObjectEffectMsg(string effectId, string objectId, string facesId, string texturePath, textureType type) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(EFFECT_ADD_TEXTURE_OBJECT_ADDR);
    oscMessage.addStringArg(effectId);
    oscMessage.addStringArg(objectId);
    oscMessage.addStringArg(facesId);
    oscMessage.addStringArg(texturePath);
    oscMessage.addIntArg(type);
    return oscMessage;
}

void OscUtil::processAddTextureObjectEffectMsg(ofxOscMessage m, ISceneHandler *sceneHandler) {
    string effId = m.getArgAsString(0);
    string objectId = m.getArgAsString(1);
    string facesId = m.getArgAsString(2);
    string texturePath = m.getArgAsString(3);
    textureType type = (textureType)(m.getArgAsInt32(4));
    sceneHandler->addTextureObjectEffect(effId, objectId, facesId, texturePath, type);
}

ofxOscMessage OscUtil::createTestEffectMsg(string effectId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(EFFECT_TEST_ADDR);
    oscMessage.addStringArg(effectId);
    return oscMessage;
}

void OscUtil::processTestEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
    string effId = msg.getArgAsString(0);
    sceneHandler->testEffect(effId);
}

ofxOscMessage OscUtil::createSetActiveCamDisplayHelpersMsg(bool display) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SET_DISPLAY_HELPERS);
    oscMessage.addIntArg(display);
    return oscMessage;
}

void OscUtil::processSetActiveCamDisplayHelpersMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    bool display = msg.getArgAsInt32(0);
    sceneHandler->setActiveCamDisplayHelpers(display);
}

ofxOscMessage OscUtil::createSetActiveCamHelperCoordMsg(bool isSrc, int pointI, ofVec2f coord) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SET_HELPER_COORD);
    oscMessage.addIntArg(isSrc);
    oscMessage.addIntArg(pointI);
    oscMessage.addFloatArg(coord[0]);
    oscMessage.addFloatArg(coord[1]);
    return oscMessage;
}

void OscUtil::processSetActiveCamHelperCoordMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    bool isSrc = msg.getArgAsInt32(0);
    int pointI = msg.getArgAsInt32(1);
    ofVec2f coord = ofVec2f(msg.getArgAsFloat(2), msg.getArgAsFloat(3));

    sceneHandler->setActiveCamHelperCoord(isSrc, pointI, coord);
}

ofxOscMessage OscUtil::createCalibrateMsg() {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_CALIBRATE);
    return oscMessage;
}

void OscUtil::processCalibrateMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    sceneHandler->calibrateActiveCam();
}

ofxOscMessage OscUtil::createResetCalibrationMsg() {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_RESETCALIBRATION);
    return oscMessage;
}

void OscUtil::processResetCalibrationMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    sceneHandler->resetActiveCamCalibraton();
}
ofxOscMessage OscUtil::createSetPerspectiveMsg(string camId, float _fov, float _aspect, float _zNear, float _zFar) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SET_PERSPECTIVE);
    oscMessage.addStringArg(camId);
    oscMessage.addFloatArg(_fov);
    oscMessage.addFloatArg(_aspect);
    oscMessage.addFloatArg(_zNear);
    oscMessage.addFloatArg(_zFar);
    return oscMessage;
}
void OscUtil::processSetPerspectiveMsg(ofxOscMessage msg, ISceneHandler *sceneHandler) {
    string camId = msg.getArgAsString(0);
    float _fov = msg.getArgAsFloat(1);
    float _aspect = msg.getArgAsFloat(2);
    float _zNear = msg.getArgAsFloat(3);
    float _zFar = msg.getArgAsFloat(4);
    sceneHandler->setPerspective(camId, _fov, _aspect, _zNear, _zFar);
}

ofxOscMessage OscUtil::createSetIsProjectorMsg(string camId, bool NewVal) {
    ofxOscMessage oscMessage;
    oscMessage.setAddress(CAMERA_SET_ISPROJECTOR);
    oscMessage.addStringArg(camId);
    oscMessage.addIntArg(NewVal);
    return oscMessage;
}

void OscUtil::processSetIsProjectorMsg(ofxOscMessage msg, ISceneHandler *sceneHandler){
        string camId = msg.getArgAsString(0);
        bool NewVal = msg.getArgAsInt32(1);
        sceneHandler->setIsProjector(camId, NewVal);
}

ofxOscMessage OscUtil::createAddLightMsg(string lightId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_ADD_ADDR);
    oscMessage.addStringArg(lightId);
    return oscMessage;
}
void OscUtil::processAddLightMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    sceneHandler->addLight(lightId);
}

ofxOscMessage OscUtil::createSetOnLightMsg(string lightId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_ON);
    oscMessage.addStringArg(lightId);
    return oscMessage;
}
void OscUtil::processSetOnLightMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    sceneHandler->setLightOn(lightId);
}
ofxOscMessage OscUtil::createSetOffLightMsg(string lightId){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_OFF);
    oscMessage.addStringArg(lightId);
    return oscMessage;
}
void OscUtil::processSetOffLightMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    sceneHandler->setLightOff(lightId);
}


ofxOscMessage OscUtil::createLightSpecularMsg(string lightId, float r, float g, float b){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_SPECULAR_ADDR);
    oscMessage.addStringArg(lightId);
    oscMessage.addFloatArg(r);
    oscMessage.addFloatArg(g);
    oscMessage.addFloatArg(b);
    return oscMessage;
}

void OscUtil::processLightSpecularMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    float r = m.getArgAsFloat(1);
    float g = m.getArgAsFloat(2);
    float b = m.getArgAsFloat(3);
    sceneHandler->setLightSpecular(lightId, r, g, b);
}

ofxOscMessage OscUtil::createLightDirectionalMsg(string lightId, float r, float g, float b, float nx, float ny, float nz){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_DIRECTIONAL_ADDR);
    oscMessage.addStringArg(lightId);
    oscMessage.addFloatArg(r);
    oscMessage.addFloatArg(g);
    oscMessage.addFloatArg(b);
    oscMessage.addFloatArg(nx);
    oscMessage.addFloatArg(ny);
    oscMessage.addFloatArg(nz);
    return oscMessage;
}

void OscUtil::processLightDirectionalMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    float r = m.getArgAsFloat(1);
    float g = m.getArgAsFloat(2);
    float b = m.getArgAsFloat(3);
    float nx = m.getArgAsFloat(4);
    float ny = m.getArgAsFloat(5);
    float nz = m.getArgAsFloat(6);
    sceneHandler->setLightDirectional(lightId, r, g, b, nx, ny, nz);
}

ofxOscMessage OscUtil::createLightSpotMsg(string lightId, float r, float g, float b, float x, float y, float z, float nx,
                   float ny, float nz, float angle, float concentration){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_SPOT_ADDR);
    oscMessage.addStringArg(lightId);
    oscMessage.addFloatArg(r);
    oscMessage.addFloatArg(g);
    oscMessage.addFloatArg(b);
    oscMessage.addFloatArg(x);
    oscMessage.addFloatArg(y);
    oscMessage.addFloatArg(z);
    oscMessage.addFloatArg(nx);
    oscMessage.addFloatArg(ny);
    oscMessage.addFloatArg(nz);
    oscMessage.addFloatArg(angle);
    oscMessage.addFloatArg(concentration);
    return oscMessage;
}

void OscUtil::processLightSpotMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    float r = m.getArgAsFloat(1);
    float g = m.getArgAsFloat(2);
    float b = m.getArgAsFloat(3);
    float x = m.getArgAsFloat(4);
    float y = m.getArgAsFloat(5);
    float z = m.getArgAsFloat(6);
    float nx = m.getArgAsFloat(7);
    float ny = m.getArgAsFloat(8);
    float nz = m.getArgAsFloat(9);
    float angle = m.getArgAsFloat(10);
    float concentr = m.getArgAsFloat(11);
    sceneHandler->setLightSpot(lightId, r, g, b, x, y, z, nx, ny, nz, angle, concentr);
}

ofxOscMessage OscUtil::createLightPointMsg(string lightId, float r, float g, float b, float x, float y, float z){
    ofxOscMessage oscMessage;
    oscMessage.setAddress(LIGHT_POINT_ADDR);
    oscMessage.addStringArg(lightId);
    oscMessage.addFloatArg(r);
    oscMessage.addFloatArg(g);
    oscMessage.addFloatArg(b);
    oscMessage.addFloatArg(x);
    oscMessage.addFloatArg(y);
    oscMessage.addFloatArg(z);
    return oscMessage;
}

void OscUtil::processLightPointMsg(ofxOscMessage m, ISceneHandler *sceneHandler){
    string lightId = m.getArgAsString(0);
    float r = m.getArgAsFloat(1);
    float g = m.getArgAsFloat(2);
    float b = m.getArgAsFloat(3);
    float x = m.getArgAsFloat(4);
    float y = m.getArgAsFloat(5);
    float z = m.getArgAsFloat(6);
    sceneHandler->setLightPoint(lightId, r, g, b, x, y, z);
}

int OscUtil::processMessageAction(ofxOscMessage m, ISceneHandler *sceneHandler) {
    if ( m.getAddress() == CAMERA_ADD_ADDR) {
        OscUtil::processAddCameraMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SETPOS_ADDR) {
        OscUtil::processSetCameraPosMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SETEYE_ADDR) {
        OscUtil::processSetCameraEyeMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SETUP_ADDR) {
        OscUtil::processSetCameraUpMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SET_DISPLAY_HELPERS) {
        OscUtil::processSetActiveCamDisplayHelpersMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SET_HELPER_COORD) {
        OscUtil::processSetActiveCamHelperCoordMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_CALIBRATE) {
        OscUtil::processCalibrateMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_RESETCALIBRATION) {
        OscUtil::processResetCalibrationMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_SET_PERSPECTIVE) {
        OscUtil::processSetPerspectiveMsg(m, sceneHandler);
    }else if ( m.getAddress() == QUAD_ADD_ADDR) {
        OscUtil::processAddQuadMsg(m, sceneHandler);
    } else if ( m.getAddress() == QUAD_SETPOINT_ADDR) {
        OscUtil::processSetQuadPointMsg(m, sceneHandler);
    } else if ( m.getAddress() == LAYER_ADD_ADDR) {
        OscUtil::processAddLayerMsg(m, sceneHandler);
    } else if ( m.getAddress() == LAYER_ENABLE_ADDR) {
        OscUtil::processEnableLayerMsg(m, sceneHandler);
    } else if ( m.getAddress() == CAMERA_ACTIVATE_ADDR) {
        OscUtil::processActivateCameraMsg(m, sceneHandler);
    } else if ( m.getAddress() == QUAD_ENABLE_ADDR) {
        OscUtil::processEnableQuadMsg(m, sceneHandler);
    } else if ( m.getAddress() == SCENE_BACKGROUND_ADDR) {
        OscUtil::processSetBackgroundMsg(m, sceneHandler);
    } else if ( m.getAddress() == SCENE_RESET) {
        OscUtil::processResetSceneMsg(m, sceneHandler);
    } else if ( m.getAddress() == GROUP_ADD_ADDR) {
        OscUtil::processAddGroupMsg(m, sceneHandler);
    } else if ( m.getAddress() == GROUP_ADDQUAD_ADDR) {
        OscUtil::processAddQuadToGroupMsg(m, sceneHandler);
    } else if ( m.getAddress() == OBJECT_ADD_ADDR) {
        OscUtil::processAddObject3dMsg(m, sceneHandler);
    } else if ( m.getAddress() == OBJECT_SET_POS) {
        OscUtil::processSetObject3DPosMsg(m, sceneHandler);
    } else if ( m.getAddress() == EFFECT_ADD_FADE_ADDR) {
        OscUtil::processAddFadeEffectMsg(m, sceneHandler);
    } else if ( m.getAddress() == EFFECT_ADD_POSITION_ADDR) {
        OscUtil::processAddPositionEffectMsg(m, sceneHandler);
    } else if ( m.getAddress() == EFFECT_ADD_TEXTURE_GROUP_ADDR) {
        OscUtil::processAddTextureGroupEffectMsg(m, sceneHandler);
    } else if ( m.getAddress() == EFFECT_ADD_TEXTURE_OBJECT_ADDR) {
        OscUtil::processAddTextureObjectEffectMsg(m, sceneHandler);
    } else if ( m.getAddress() == EFFECT_TEST_ADDR) {
        OscUtil::processTestEffectMsg(m, sceneHandler);
    } else if ( m.getAddress() == LIGHT_ADD_ADDR) {
        OscUtil::processAddLightMsg(m, sceneHandler);
    } else if ( m.getAddress() == LIGHT_ON) {
        OscUtil::processSetOnLightMsg(m, sceneHandler);
    }else if ( m.getAddress() == LIGHT_OFF) {
        OscUtil::processSetOffLightMsg(m, sceneHandler);
    }else if ( m.getAddress() == LIGHT_SPECULAR_ADDR) {
        OscUtil::processLightSpecularMsg(m, sceneHandler);
    } else if ( m.getAddress() == LIGHT_DIRECTIONAL_ADDR) {
        OscUtil::processLightDirectionalMsg(m, sceneHandler);
    } else if ( m.getAddress() == LIGHT_SPOT_ADDR) {
        OscUtil::processLightSpotMsg(m, sceneHandler);
    } else if ( m.getAddress() == LIGHT_POINT_ADDR) {
        OscUtil::processLightPointMsg(m, sceneHandler);
    } else {
        return -1;
    }
    return 1;
}
