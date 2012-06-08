#pragma once

#include "ISerializable.h"
#include "ofMain.h"
#include "Layer2D.h"

class ofxCamera: public ISerializable {
public:
	ofxCamera();

	void position(float x, float y, float z);
	void position(ofVec3f _pos);
	void position(); //reset the position to initial values

	void eye(float _x, float _y, float _z);
	void eye(ofVec3f _eye);
	void eye(); //reset eye psition to the initial values
	void up(float _x, float _y, float _z);
	void up(ofVec3f _up);
	void up(); //reset up vector to initial values

	float getfieldOfView();
	float getaspectRatio();
	float getzNear();
	float getzFar();

	void perspective(float _fov, float _aspect, float _zNear, float _zFar);
	void perspective();//reset perspective to initial values

	virtual void place(); //this must go in the draw function!!!!
	void remove(); //Removes the camera, so it returns as if there was no camera

	void moveLocal(float _x, float _y, float _z); //Moves the camera along it's own coordinatesystem
	void moveLocal(ofVec3f move);
	void moveGlobal(float _x, float _y, float _z); //Moves the camera along the global coordinatesystem
	void moveGlobal(ofVec3f move);

	void orbitAround(ofVec3f target, ofVec3f axis, float value);
	void rotate(ofVec3f axis, float value);

	ofVec3f getDir();
	ofVec3f getPosition();
	ofVec3f getEye();
	ofVec3f getUp();

	void setId(string id);
	string getId();

    void drawCamera();
    bool isProjector();
    void setIsProjector(bool);

    void drawLayers();

    //resolucion de la ventana en el nodo.
    void setClientResolution(int resx, int resy);

    Layer2D* addLayer2D(string id);
    Layer2D* getLayer2D(string id);
    map<string, Layer2D*> getLayers2D();

    SerializedNode* Serialize();

    void calculateHomography();
    void resetHomography();

    void setDisplayHelpers(bool);
    void setSrcHelperCoord(int i, ofVec2f coord);
    void setDstHelperCoord(int i, ofVec2f coord);
    ofVec2f getSrcHelperCoord(int i);
    ofVec2f getDstHelperCoord(int i);

protected:
	ofVec3f posCoord;
	ofVec3f eyeCoord;
	ofVec3f upVec;

	//relative to defining the persperctive:
	float	fieldOfView;
	int	w;
	int	h;
	float	aspectRatio;
	float zNear, zFar;

private:
	bool projector;
	string id;
    map<string, Layer2D*> layers2D;
    int clientX, clientY;

    void SetupScreen_ext();

    GLfloat homographyMatrix[16];

    bool displayHelpers;

    ofVec2f helperSrc[4];
    ofVec2f helperDst[4];

    float helpersRadius;

};



