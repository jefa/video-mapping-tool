#include "ofxCamera.h"
#include "homography.h"
#include "glut.h"

#include <cmath>

map<string, Layer2D*>::iterator layersIt;

ofxCamera::ofxCamera() {
	perspective();
	position();
	eye();
	up();

	clientX = glutGet(GLUT_WINDOW_WIDTH);
	clientY = glutGet(GLUT_WINDOW_HEIGHT);

	resetHomography();
	displayHelpers = false;

    helpersRadius = 5.0f;

    helperSrc[0]=ofVec2f(20,20);
    helperSrc[1]=ofVec2f(40,20);
    helperSrc[2]=ofVec2f(40,40);
    helperSrc[3]=ofVec2f(20,40);

    helperDst[0]=ofVec2f(0,0);
    helperDst[1]=ofVec2f(60,0);
    helperDst[2]=ofVec2f(60,60);
    helperDst[3]=ofVec2f(0,60);
}

void ofxCamera::setClientResolution(int resx, int resy) {
    clientX = resx;
    clientY = resy;
}

void ofxCamera::setId(string id){
    this->id = id;
}

string ofxCamera::getId(){
    return this->id;
}

void ofxCamera::position(float x, float y, float z) {
	posCoord.x = x;
	posCoord.y = y;
	posCoord.z = z;
}

void ofxCamera::position(ofVec3f _pos) {
	posCoord = _pos;
}

void ofxCamera::position() {
    posCoord.x = 0.0f;
    posCoord.y = 0.0f;
	float halfFov = PI * fieldOfView / 360.0f;
	float theTan = tanf(halfFov);
	posCoord.z = posCoord.y/theTan;
}

void ofxCamera::eye(float x, float y, float z) {
	eyeCoord.x = x;
	eyeCoord.y = y;
	eyeCoord.z = z;
}

void ofxCamera::eye(ofVec3f _pos) {
	eyeCoord = _pos;
}

void ofxCamera::eye() {
    eyeCoord.x = 0;
    eyeCoord.y = 0;
	eyeCoord.z = 0;
}

void ofxCamera::up(float _nx, float _ny, float _nz) {
	upVec.x = _nx;
	upVec.y = _ny;
	upVec.z = _nz;
}

void ofxCamera::up(ofVec3f _up) {
	upVec = _up;
}

void ofxCamera::up() {
	upVec.x = 0;
	upVec.y = 1;
	upVec.z = 0;
}

void ofxCamera::perspective(float _fov, float _aspect, float _zNear, float _zFar) {
	fieldOfView = _fov;
	aspectRatio = _aspect;
	if(_zNear==0) _zNear = 0.01;
	zNear = _zNear;
	zFar = _zFar;
}
float ofxCamera::getfieldOfView(){
    return this->fieldOfView;
}
float ofxCamera::getaspectRatio(){
    return this->aspectRatio;
}
float ofxCamera::getzNear(){
    return this->zNear;
}
float ofxCamera::getzFar(){
    return this->zFar;
}
void ofxCamera::perspective() {
	fieldOfView = 65.0f;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);
	aspectRatio = (float)w/(float)h;
	zNear = 1.0f;
	zFar = 10000.0f;
}

void ofxCamera::place() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posCoord[0], posCoord[1], posCoord[2], eyeCoord[0], eyeCoord[1], eyeCoord[2], upVec[0], upVec[1], upVec[2]);

	// the coordinate system here is based on 2d geometry:
	// down = +y
	// right = +x
	// out of screen = +z
	// this is a bit different from the usual 3d coordinate systems,
	// where +y is up instead of down
}

//Similar a ofSetupScreen pero utilizando la resolucion del cliente.
void ofxCamera::SetupScreen_ext(){
	int w, h;

	//w = ofGetWidth();
	//h = ofGetHeight();
	w = clientX;
	h = clientY;

	float halfFov, theTan, screenFov, aspect;
	screenFov 		= 60.0f;

	float eyeX 		= (float)w / 2.0;
	float eyeY 		= (float)h / 2.0;
	halfFov 		= PI * screenFov / 360.0;
	theTan 			= tanf(halfFov);
	float dist 		= eyeY / theTan;
	float nearDist 	= dist / 10.0;	// near / far clip plane
	float farDist 	= dist * 10.0;
	aspect 			= (float)w/(float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(screenFov, aspect, nearDist, farDist);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, dist, eyeX, eyeY, 0.0, 0.0, 1.0, 0.0);

	glScalef(1, -1, 1);           // invert Y axis so increasing Y goes down.
  	glTranslatef(0, -h, 0);       // shift origin up to upper-left corner.
}

//Removes the camera, so it returns as if there was no camera
void ofxCamera::remove() {
	SetupScreen_ext();
}

void ofxCamera::moveLocal(float _x, float _y, float _z) {
	moveLocal(ofVec3f(_x, _y, _z));
}

void ofxCamera::moveLocal(ofVec3f move) {
	ofVec3f dir =  getDir().normalized();
	posCoord += dir.rescaled(move.z);
	eyeCoord += dir.rescaled(move.z);

	posCoord += upVec.rescaled(move.y);
	eyeCoord += upVec.rescaled(move.y);

	posCoord += dir.getCrossed(upVec).rescaled(move.x);
	eyeCoord += dir.getCrossed(upVec).rescaled(move.x);
}

void ofxCamera::moveGlobal(float _x, float _y, float _z) {
	posCoord.x += _x;
	posCoord.y += _y;
	posCoord.z += _z;
	eyeCoord.x += _x;
	eyeCoord.y += _y;
	eyeCoord.z += _z;
}

void ofxCamera::moveGlobal(ofVec3f move) {
	posCoord += move;
	eyeCoord += move;
}

void ofxCamera::orbitAround(ofVec3f target, ofVec3f axis, float angle) {
	ofVec3f r = posCoord-target;
	posCoord = target + r.rotated(angle, axis);
}

void ofxCamera::rotate(ofVec3f axis, float angle) {
	ofVec3f r = -posCoord+eyeCoord;
	eyeCoord = posCoord + r.rotated(angle, axis);
}

//
//Getters
//
ofVec3f ofxCamera::getDir() {
	return eyeCoord-posCoord;
}

ofVec3f ofxCamera::getPosition() {
	return posCoord;
}

ofVec3f ofxCamera::getEye() {
	return eyeCoord;
}

ofVec3f ofxCamera::getUp() {
	return upVec;
}

bool ofxCamera::isProjector(){
    return projector;
}

void ofxCamera::setIsProjector(bool projector){
    this->projector = projector;
}

Layer2D* ofxCamera::addLayer2D(string id) {
    Layer2D* layer = new Layer2D(id);
    layers2D.insert(pair<string, Layer2D*>(id, layer));
    return layer;
}

Layer2D* ofxCamera::getLayer2D(string id) {
    return layers2D[id];
}

map<string, Layer2D*> ofxCamera::getLayers2D() {
    return layers2D;
}

void ofxCamera::setDisplayHelpers(bool display) {
    displayHelpers = display;
}

void ofxCamera::setSrcHelperCoord(int i, ofVec2f coord) {
    if(i >= 0 || i <= 3) {
        helperSrc[i] = coord;
    }
    else {
        ofLog(OF_LOG_ERROR, "ofxCamera::setSrcHelperCoord: index %i outside [0,3] range.", i);
    }
}

void ofxCamera::setDstHelperCoord(int i, ofVec2f coord) {
    if(i >= 0 || i <= 3) {
        helperDst[i] = coord;
    }
    else {
        ofLog(OF_LOG_ERROR, "ofxCamera::setDstHelperCoord: index %i outside [0,3] range.", i);
    }
}

ofVec2f ofxCamera::getSrcHelperCoord(int i) {
    if(i >= 0 || i <= 3) {
        return helperSrc[i];
    }
    else {
        ofLog(OF_LOG_ERROR, "ofxCamera::getSrcHelperCoord: index %i outside [0,3] range.", i);
        return ofVec2f(0,0);
    }
}

ofVec2f ofxCamera::getDstHelperCoord(int i) {
    if(i >= 0 || i <= 3) {
        return helperDst[i];
    }
    else {
        ofLog(OF_LOG_ERROR, "ofxCamera::getDstHelperCoord: index %i outside [0,3] range.", i);
        return ofVec2f(0,0);
    }
}

void ofxCamera::calculateHomography() {
    findHomography(helperSrc,helperDst,homographyMatrix);
}

void ofxCamera::resetHomography() {
    homographyMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
}

void ofxCamera::drawLayers() {
    glPushMatrix();
    glMultMatrixf(homographyMatrix);
    glPushMatrix();

    for(layersIt = layers2D.begin(); layersIt != layers2D.end(); layersIt++) {
        layersIt->second->draw();
    }

    glPopMatrix();
    glPopMatrix();

    if(displayHelpers) {
        for(int i = 0; i < 4; i++) {

            glColor4f(1.0f, 0.3f, 0.3f, 1.0f);
            ofCircle(helperSrc[i].x, helperSrc[i].y, helpersRadius);

            glColor4f(0.3f, 0.3f, 1.0f, 1.0f);
            ofCircle(helperDst[i].x, helperDst[i].y, helpersRadius);

            ofLine(helperSrc[i].x, helperSrc[i].y, helperDst[i].x, helperDst[i].y);
        }
    }
}

void ofxCamera::drawCamera(){

    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT );
    glDepthFunc(GL_ALWAYS);
    glDisable(GL_LIGHTING);
    glColor3f(.8f,.8f,.8f);

    //ofCircle(getPosition()[0], getPosition()[1], 2);
    glutSolidSphere(5, 1, 1);

    /*glBegin(GL_LINES);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax0[0],ax0[1],ax0[2]);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax1[0],ax1[1],ax1[2]);
        glVertex3f(pos[0],pos[1],pos[2]); 	glVertex3f(ax2[0],ax2[1],ax2[2]);
    glEnd();*/

    ofVec3f lVec = getDir();
    ofVec3f upVec = getUp();
    ofVec3f rightVec = lVec.crossed(upVec);
    //printf("================= Vector L:     (%f,%f,%f)\n", lVec[0],lVec[1],lVec[2]);
    //printf("================= Vector UP:    (%f,%f,%f)\n", upVec[0],upVec[1],upVec[2]);
    //printf("================= Vector RIGHT: (%f,%f,%f)\n", rightVec[0],rightVec[1],rightVec[2]);

    glColor3f(1.0, 1.0, 0.0);

    float length = lVec.length();
    float fovRadians = ofDegToRad(this->fieldOfView);
    float apHf = 2 * length * tan ( fovRadians / 2 );
    float apVf = apHf / aspectRatio;
    //printf("================= Vector FOV: %f, %f\n", this->fieldOfView, fovRadians);
    //printf("================= Vector LVEC length: %f\n", length);
    //printf("================= Vector ASPECTRATIO: %f \n", aspectRatio);
    //printf("================= Vector APH: %f ::: APV: %f\n", apHf, apVf);

    ofVec3f vecUp =  upVec * apVf / 2; //(0, apVf/2, eye[2]);
    ofVec3f vecRight = rightVec * apHf ; //(apHf/2, 0, eye[2]);

    ofVec3f p1 = lVec - vecRight + vecUp;
    ofVec3f p2 = lVec + vecRight + vecUp;
    ofVec3f p3 = lVec - vecRight - vecUp;
    ofVec3f p4 = lVec + vecRight - vecUp;

    //printf("================= Vector P1:  (%f,%f,%f)\n", p1[0],p1[1],p1[2]);
    //printf("================= Vector P2:  (%f,%f,%f)\n", p2[0],p2[1],p2[2]);
    //printf("================= Vector P3:  (%f,%f,%f)\n", p3[0],p3[1],p3[2]);
    //printf("================= Vector P4:  (%f,%f,%f)\n", p4[0],p4[1],p4[2]);

    glBegin(GL_LINES);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p1[0],p1[1],p1[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p2[0],p2[1],p2[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p3[0],p3[1],p3[2]);
        glVertex3f(getPosition()[0],getPosition()[1],getPosition()[2]); 	glVertex3f(p4[0],p4[1],p4[2]);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(p1[0],p1[1],p1[2]);
        glVertex3f(p2[0],p2[1],p2[2]);
        glVertex3f(p4[0],p4[1],p4[2]);
        glVertex3f(p3[0],p3[1],p3[2]);
    glEnd();

    glPopAttrib();

    //printf("\n");
}

SerializedNode* ofxCamera::Serialize() {
    SerializedNode* node = new SerializedNode("camera");

    node->addAttribute("id", this->id);
    node->addAttribute("projector", this->projector);

    SerializedNode* viewNode = new SerializedNode("view");
    viewNode->addAttribute("pos", posCoord);
    viewNode->addAttribute("eye", eyeCoord);
    viewNode->addAttribute("up", upVec);

    node->addChildNode(viewNode);

    SerializedNode* projectionNode = new SerializedNode("projection");
    projectionNode->addAttribute("fov", fieldOfView);
    projectionNode->addAttribute("aspect", aspectRatio);
    projectionNode->addAttribute("resx", clientX);
    projectionNode->addAttribute("resy", clientY);

    node->addChildNode(projectionNode);

    SerializedNode* layersNode = new SerializedNode("layers");
    for(layersIt = layers2D.begin(); layersIt != layers2D.end(); layersIt++) {
        layersNode->addChildNode(layersIt->second->Serialize());
    }
    node->addChildNode(layersNode);

    return node;
}
