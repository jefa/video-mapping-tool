#ifndef _VMTNODE
#define _VMTNODE

#include "ofMain.h"
#include "ofxOsc.h"

#include "Scene.h"
#include "ISceneHandler.h"

// listen on port 12345
#define PORT 54321


class VmtNode : public ofBaseApp, public ISceneHandler {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		// ISceneHandler

        void resetScene();
        void setBackground(float, float, float);

        void addCamera(string id);
        void setCameraPos(string camId, float x, float y, float z);
        void setCameraEye(string camId, float x, float y, float z);
        void setCameraUp(string camId, float x, float y, float z);
        void activateCamera(string camId);
        void setPerspective(string camId, float _fov, float _aspect, float _zNear, float _zFar);
        void setIsProjector(string camId, bool NewValue);
        ofxCamera* getActiveCamera();

        void addGroup(string groupId);
        QuadGroup* getGroup(string groupId);

        void addLayer(string camId, string layerId);
        void addQuad(string camId, string layerId, string quadId);
        void addQuadToGroup(string groupId, string camId, string layerId, string quadId);
        void enableQuad(string camId, string layerId, string quadId, bool enabled);
        void enableLayer(string camId, string layerId, bool enabled);
        void setQuadPoint(string camId, string layerId, string quadId,
                  int point, float coordX, float coordY);
        void addObject3D(string objId, string path);
        Object3D* getObject3D(string objId);
        void setObject3D(string objId,int aParam, float aValue);

        void addPositionEffect(string effectId, string objId, ofVec3f posIni, ofVec3f posFin, float delay);
        void addFadeEffect(string effectId, string groupId, ofVec4f colorIni, ofVec4f colorFin, float delay);
        void addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type);
        void addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type);

        void testEffect(string id);

        void setActiveCamDisplayHelpers(bool display);
        void setActiveCamHelperCoord(bool isSrc, int pointI, ofVec2f coord);
        void calibrateActiveCam();
        void resetActiveCamCalibraton();

        void addLight(string lightId);
        void setLightOn(string lightId);
        void setLightOff(string lightId);
        void setLightSpecular(string lightId, float r, float g, float b);
        void setLightDirectional(string lightId, float r, float g, float b,
                                           float nx, float ny, float nz);
        void setLightSpot(string lightId, float r, float g, float b,
                                           float x, float y, float z,
                                           float nx, float ny, float nz,
                                           float angle, float concentration);
        void setLightPoint(string lightId, float r, float g, float b,
                                           float x, float y, float z);


private:
		ofxOscReceiver	receiver;
		Scene *scene;
};

#endif
