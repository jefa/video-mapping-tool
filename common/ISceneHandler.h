#ifndef ISCENEHANDLER_H_INCLUDED
#define ISCENEHANDLER_H_INCLUDED

#include "Scene.h"

class ISceneHandler
{
    public:
        virtual void resetScene() =0;

        virtual void setBackground(float, float, float) =0;

        virtual void addCamera(string id) =0;
        virtual void setCameraPos(string camId, float x, float y, float z) =0;
        virtual void setCameraEye(string camId, float x, float y, float z) =0;
        virtual void setCameraUp(string camId, float x, float y, float z) =0;
        virtual void activateCamera(string camId) =0;
        virtual void setPerspective(string camId, float _fov, float _aspect, float _zNear, float _zFar)=0;
        virtual void setIsProjector(string camId, bool NewValue)=0;
        virtual ofxCamera* getActiveCamera() =0;

        virtual void addGroup(string groupId) =0;
        virtual QuadGroup* getGroup(string groupId) =0;

        virtual void addLayer(string camId, string layerId) =0;
        virtual void addQuad(string camId, string layerId, string quadId) =0;
        virtual void addQuadToGroup(string groupId, string camId, string layerId, string quadId) =0;
        virtual void enableQuad(string camId, string layerId, string quadId, bool enabled) =0;
        virtual void enableLayer(string camId, string layerId, bool enabled) =0;
        virtual void setQuadPoint(string camId, string layerId, string quadId,
                  int point, float coordX, float coordY) =0;
        virtual void addObject3D(string objId, string path) =0;
        virtual void setObject3D(string objId, int aParam, float aValue) =0;
        virtual Object3D* getObject3D(string objId) =0;

        virtual void addPositionEffect(string effectId, string objId, ofVec3f posIni, ofVec3f posFin, float delay) =0;
        virtual void addFadeEffect(string effectId, string groupId, ofVec4f colorIni, ofVec4f colorFin, float delay) =0;

        virtual void addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type) =0;
        virtual void addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type) =0;

        virtual void testEffect(string id) =0;

        virtual void setActiveCamDisplayHelpers(bool display) =0;
        virtual void setActiveCamHelperCoord(bool isSrc, int pointI, ofVec2f coord) =0;
        virtual void calibrateActiveCam() =0;
        virtual void resetActiveCamCalibraton() =0;

        virtual void addLight(string lightId) =0;
        virtual void setLightSpecular(string lightId, float r, float g, float b) =0;
        virtual void setLightDirectional(string lightId, float r, float g, float b,
                                           float nx, float ny, float nz) =0;
        virtual void setLightSpot(string lightId, float r, float g, float b,
                                           float x, float y, float z,
                                           float nx, float ny, float nz,
                                           float angle, float concentration) =0;
        virtual void setLightPoint(string lightId, float r, float g, float b,
                                           float x, float y, float z) =0;
        virtual void setLightOff(string lightId)=0;
        virtual void setLightOn(string lightId)=0;
};

#endif // ISCENEHANDLER_H_INCLUDED
