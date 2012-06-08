#ifndef OSCUTIL_H
#define OSCUTIL_H

#include "ofxOsc.h"

#include "ISceneHandler.h"
#include "Effect.h"

const string LAYER_ADD_ADDR                 = "/layer/add";
const string CAMERA_ADD_ADDR                = "/camera/add";
const string CAMERA_SETPOS_ADDR             = "/camera/setpos";
const string CAMERA_SETEYE_ADDR             = "/camera/seteye";
const string CAMERA_SETUP_ADDR              = "/camera/setup";
const string CAMERA_ACTIVATE_ADDR           = "/camera/activate";
const string CAMERA_SET_PERSPECTIVE         = "/camera/setperspective";
const string CAMERA_SET_ISPROJECTOR         = "/camera/setisprojector";
const string CAMERA_SET_DISPLAY_HELPERS     = "/camera/setdisplayhelpers";
const string CAMERA_SET_HELPER_COORD        = "/camera/sethelpercoord";
const string CAMERA_CALIBRATE               = "/camera/calibrate";
const string CAMERA_RESETCALIBRATION        = "/camera/resetcalibration";
const string QUAD_ADD_ADDR                  = "/quad/add";
const string QUAD_SETPOINT_ADDR             = "/quad/setpoint";
const string QUAD_ENABLE_ADDR               = "/quad/enable";
const string LAYER_ENABLE_ADDR              = "/layer/enable";
const string SCENE_BACKGROUND_ADDR          = "/scene/setbackground";
const string SCENE_RESET                    = "/scene/reset";
const string GROUP_ADD_ADDR                 = "/group/add";
const string GROUP_ADDQUAD_ADDR             = "/group/addquad";
const string OBJECT_ADD_ADDR                = "/object/add";
const string OBJECT_SET_POS                 = "/object/set_position";
const string EFFECT_ADD_FADE_ADDR           = "/effect/add_fade";
const string EFFECT_ADD_POSITION_ADDR       = "/effect/add_position";
const string EFFECT_ADD_TEXTURE_GROUP_ADDR  = "/effect/add_texture_group";
const string EFFECT_ADD_TEXTURE_OBJECT_ADDR = "/effect/add_texture_object";
const string EFFECT_TEST_ADDR               = "/effect/test";
const string LIGHT_ADD_ADDR                 = "/light/add";
const string LIGHT_SPECULAR_ADDR            = "/light/specular";
const string LIGHT_DIRECTIONAL_ADDR         = "/light/directional";
const string LIGHT_SPOT_ADDR                = "/light/spot";
const string LIGHT_POINT_ADDR               = "/light/point";
const string LIGHT_ON                       = "/light/on";
const string LIGHT_OFF                      = "/light/off";

class OscUtil
{
    public:
        OscUtil();
        virtual ~OscUtil();

        static ofxOscMessage createResetSceneMsg();
        static void processResetSceneMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetBackgroundMsg(float r, float g, float b);
        static void processSetBackgroundMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddCameraMsg(string id);
        static void processAddCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetCameraPosMsg(string id, ofVec3f position);
        static void processSetCameraPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetCameraEyeMsg(string id, ofVec3f eye);
        static void processSetCameraEyeMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetCameraUpMsg(string id, ofVec3f up);
        static void processSetCameraUpMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createActivateCameraMsg(string id);
        static void processActivateCameraMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetPerspectiveMsg(string camId, float _fov, float _aspect, float _zNear, float _zFar);
        static void processSetPerspectiveMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetIsProjectorMsg(string id, bool NewVal);
        static void processSetIsProjectorMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddQuadMsg(string camId, string layerId, string quadId);
        static void processAddQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetQuadPointMsg(string camId, string layerId, string quadId,
                                                   int point, float coordX, float coordY);
        static void processSetQuadPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createEnableQuadMsg(string camId, string layerId, string quadId, bool enabled);
        static void processEnableQuadMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddLayerMsg(string camId, string layerId);
        static void processAddLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createEnableLayerMsg(string camId, string layerId, bool enabled);
        static void processEnableLayerMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddGroupMsg(string groupId);
        static void processAddGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createAddQuadToGroupMsg(string groupId, string camId, string layerId, string quadId);
        static void processAddQuadToGroupMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddObject3dMsg(string objId, string base64data);
        static void processAddObject3dMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetObject3DPosMsg(string objId, int aParam, float aValue);
        static void processSetObject3DPosMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddPositionEffectMsg(string effectId, string objId, ofVec3f posIni,
                                                        ofVec3f posFin, float delay);
        static void processAddPositionEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createAddFadeEffectMsg(string effectId, string groupId, ofVec4f colorIni,
                                                    ofVec4f colorFin, float delay);
        static void processAddFadeEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddTextureGroupEffectMsg(string effectId, string groupId, string texturePath, textureType type);
        static void processAddTextureGroupEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddTextureObjectEffectMsg(string effectId, string objectId, string facesId, string texturePath, textureType type);
        static void processAddTextureObjectEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createTestEffectMsg(string effectId);
        static void processTestEffectMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetActiveCamDisplayHelpersMsg(bool display);
        static void processSetActiveCamDisplayHelpersMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetActiveCamHelperCoordMsg(bool isSrc, int pointI, ofVec2f coord);
        static void processSetActiveCamHelperCoordMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createCalibrateMsg();
        static void processCalibrateMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createResetCalibrationMsg();
        static void processResetCalibrationMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createSetOffLightMsg(string lightId);
        static void processSetOffLightMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createSetOnLightMsg(string lightId);
        static void processSetOnLightMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static ofxOscMessage createAddLightMsg(string lightId);
        static void processAddLightMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightSpecularMsg(string lightId, float r, float g, float b);
        static void processLightSpecularMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightDirectionalMsg(string lightId, float r, float g, float b, float nx, float ny, float nz);
        static void processLightDirectionalMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightSpotMsg(string lightId, float r, float g, float b, float x, float y, float z, float nx,
                           float ny, float nz, float angle, float concentration);
        static void processLightSpotMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);
        static ofxOscMessage createLightPointMsg(string lightId, float r, float g, float b, float x, float y, float z);
        static void processLightPointMsg(ofxOscMessage msg, ISceneHandler *sceneHandler);

        static int processMessageAction(ofxOscMessage, ISceneHandler *);

    protected:
    private:
};

#endif // OSCUTIL_H
