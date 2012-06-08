#include "vmtnode.h"

#include "OscUtil.h"
#include "FadeEffect.h"
#include "PositionEffect.h"
#include "TextureEffect.h"

//--------------------------------------------------------------
void VmtNode::setup(){

    //ofSetLogLevel(OF_LOG_VERBOSE);

    //for smooth animation, set vertical sync if we can
	ofSetVerticalSync(true);
	// also, frame rate:
	ofSetFrameRate(60);

	ofSetVerticalSync(true);
	glEnable(GL_DEPTH_TEST); //lights look weird if depth test is not enabled

    scene = new Scene();

	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup( PORT );

}

//--------------------------------------------------------------
void VmtNode::update(){

	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );

        if ( !OscUtil::processMessageAction(m, this) )
		{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for ( int i=0; i<m.getNumArgs(); i++ )
			{
				// get the argument type
				msg_string += m.getArgTypeName( i );
				msg_string += ":";
				// display the argument - make sure we get the right type
				if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
					msg_string += ofToString( m.getArgAsInt32( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
					msg_string += ofToString( m.getArgAsFloat( i ) );
				else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
					msg_string += m.getArgAsString( i );
				else
					msg_string += "unknown";
			}
			printf("MENSAJE INVALIDO: %s\n", msg_string.c_str());
		}
	}
	scene->update();
}


//--------------------------------------------------------------
void VmtNode::draw(){

	scene->draw();
}


//--------------------------------------------------------------
void VmtNode::keyPressed  (int key){

}

//--------------------------------------------------------------
void VmtNode::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void VmtNode::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void VmtNode::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void VmtNode::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void VmtNode::windowResized(int w, int h){

}

// ISceneHandler interface implementation

void VmtNode::resetScene() {
    delete scene;
}

void VmtNode::setBackground(float r, float g, float b){
    scene->setBackground(r,g,b);
}

void VmtNode::addCamera(string id){
    scene->addCamera(id);
    scene->activateCamera(id);
}

void VmtNode::setCameraPos(string camId, float x, float y, float z){
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->position(x, y, z);
}

void VmtNode::setCameraEye(string camId, float x, float y, float z){
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->eye(x, y, z);
}

void VmtNode::setCameraUp(string camId, float x, float y, float z){
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->up(x, y, z);
}

void VmtNode::activateCamera(string camId){
    scene->activateCamera(camId);
}
void VmtNode::setPerspective(string camId, float _fov, float _aspect, float _zNear, float _zFar){
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->perspective(_fov, _aspect, _zNear, _zFar);
}
void VmtNode::setIsProjector(string camId, bool NewValue){
        ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL)
        camera->setIsProjector(NewValue);

}

ofxCamera* VmtNode::getActiveCamera(){
    return scene->getActiveCamera();
}

void VmtNode::addGroup(string groupId){
    scene->addGroup(groupId);
}

QuadGroup* VmtNode::getGroup(string groupId){
    return scene->getGroup(groupId);
}

void VmtNode::addLayer(string camId, string layerId){
    if (scene->getCamera(camId) != NULL)
        scene->getCamera(camId)->addLayer2D(layerId);
}

void VmtNode::enableLayer(string camId, string layerId, bool enabled){
    ofxCamera *camera = scene->getCamera(camId);
    if (camera != NULL) {
        Layer2D *layer = camera->getLayer2D(layerId);
        if (layer != NULL){
            layer->setEnabled(enabled);
        }
    }
}

void VmtNode::addQuad(string camId, string layerId, string quadId){
    if (scene->getCamera(camId) != NULL) {
        ofxCamera *camera = scene->getCamera(camId);
        if (camera->getLayer2D(layerId) != NULL)
            camera->getLayer2D(layerId)->addQuad2D(quadId);
    }
}

void VmtNode::addQuadToGroup(string groupId, string camId, string layerId, string quadId){
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

void VmtNode::enableQuad(string camId, string layerId, string quadId, bool enabled){
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

void VmtNode::setQuadPoint(string camId, string layerId, string quadId,
            int point, float coordX, float coordY){
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

void VmtNode::addObject3D(string objId, string path){
    scene->addObject3D(objId, path);
}
void VmtNode::setObject3D(string objId, int aParam, float aValue){
    scene->setObject3D(objId, aParam, aValue);
}

Object3D* VmtNode::getObject3D(string objId){
    return scene->getObject3D(objId);
}

void VmtNode::addPositionEffect(string effectId, string objId, ofVec3f posIni, ofVec3f posFin, float delay){
    if (scene->getObject3D(objId) == NULL){
        printf("VmtNode::addPositionEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    scene->addEffect(effectId, new PositionEffect(effectId, scene->getObject3D(objId), posIni, posFin, delay));
}

void VmtNode::addFadeEffect(string effectId, string groupId, ofVec4f colorIni, ofVec4f colorFin, float delay){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtNode::addFadeEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    scene->addEffect(effectId, new FadeEffect(effectId, scene->getGroup(groupId), colorIni, colorFin, delay));
}

void VmtNode::addTextureGroupEffect(string effectId, string groupId, string texturePath, textureType type){
    if (scene->getGroup(groupId) == NULL){
        printf("VmtNode::addTextureGroupEffect: group does not exists(%s)\n", groupId.c_str());
        return;
    }
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getGroup(groupId), texturePath, type));
}

void VmtNode::addTextureObjectEffect(string effectId, string objId, string facesId, string texturePath, textureType type) {
    if (scene->getObject3D(objId) == NULL){
        printf("VmtNode::addTextureObjectEffect: object does not exists(%s)\n", objId.c_str());
        return;
    }
    scene->addEffect(effectId, new TextureEffect(effectId, scene->getObject3D(objId), facesId, texturePath, type));
}

void VmtNode::testEffect(string id){
    if (scene->getEffects()[id] == NULL){
        printf("VmtNode::testEffect: efect does not exists(%s)\n", id.c_str());
        return;
    }
    this->scene->testEffect(id);
}

void VmtNode::setActiveCamDisplayHelpers(bool display) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    cam->setDisplayHelpers(display);
}

void VmtNode::setActiveCamHelperCoord(bool isSrc, int pointI, ofVec2f coord) {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    if(isSrc)
        cam->setSrcHelperCoord(pointI, coord);
    else
        cam->setDstHelperCoord(pointI, coord);
}

void VmtNode::calibrateActiveCam() {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    cam->calculateHomography();
}

void VmtNode::resetActiveCamCalibraton() {
    ofxCamera *cam = scene->getActiveCamera();
    if(cam == NULL)
        return;

    cam->resetHomography();
}

void VmtNode::setLightOff(string lightId){
    scene->setLightOff(lightId);
}
void VmtNode::setLightOn(string lightId){
    scene->setLightOn(lightId);
}
void VmtNode::addLight(string lightId){
    scene->addLight(lightId);
}

void VmtNode::setLightSpecular(string lightId, float r, float g, float b){
    if (scene->getLight(lightId) == NULL){
        printf("VmtNode::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    scene->getLight(lightId)->specular(r, g, b);
}

void VmtNode::setLightDirectional(string lightId, float r, float g, float b,
                                   float nx, float ny, float nz){
    if (scene->getLight(lightId) == NULL){
        printf("VmtNode::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    scene->getLight(lightId)->directionalLight(r, g, b, nx, ny, nz);
}

void VmtNode::setLightSpot(string lightId, float r, float g, float b,
                                   float x, float y, float z,
                                   float nx, float ny, float nz,
                                   float angle, float concentration){
    if (scene->getLight(lightId) == NULL){
        printf("VmtNode::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    scene->getLight(lightId)->spotLight(r, g, b, x, y, z, nx, ny, nz, angle, concentration);
}

void VmtNode::setLightPoint(string lightId, float r, float g, float b,
                                   float x, float y, float z){
    if (scene->getLight(lightId) == NULL){
        printf("VmtNode::setLightSpecular: light does not exists(%s)\n", lightId.c_str());
        return;
    }
    scene->getLight(lightId)->pointLight(r, g, b, x, y, z);
}

// End
