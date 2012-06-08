#include "ofMain.h"
#include "vmtnode.h"
#include "ofAppGlutWindow.h"

//========================================================================
const int minResWidth = 640;
const int maxResWidth = 2048;
const int minResHeight = 480;
const int maxResHeight = 2048;
const int minPosWinX = -2048;
const int maxPosWinX = 2048;
const int minPosWinY = 0;
const int maxPosWinY = 1024;

int main( int argc, char** argv ) {

    int resWidth, resHeight, posWinX, posWinY;
    if (argc != 5 && argc != 1){
        ofLog(OF_LOG_ERROR, "Debe iniciar el programa con 5 argumentos: %s resWidth resHeight posWinX posWinY", argv[0]);
        return -1;
    }
    else if(argc == 1) {
        ofLog(OF_LOG_WARNING, "Iniciando el programa con la configuración de pantalla por defecto");
        resWidth = 640;
        resHeight = 480;
        posWinX = 50;
        posWinY = 50;
    }
    else {
        resWidth = atoi(argv[1]);
        resHeight = atoi(argv[2]);
        posWinX = atoi(argv[3]);
        posWinY = atoi(argv[4]);

        if(resWidth > maxResWidth || resWidth < minResWidth) {
            ofLog(OF_LOG_ERROR, "el argumento resWidth debe estar entre %i y %i", minResWidth, maxResWidth);
            return -1;
        }
        if(resHeight > maxResHeight || resHeight < minResHeight) {
            ofLog(OF_LOG_ERROR, "el argumento resHeight debe estar entre %i y %i", minResHeight, maxResHeight);
            return -1;
        }
        if(posWinX > maxPosWinX || posWinX < minPosWinX) {
            ofLog(OF_LOG_ERROR, "el argumento posWinX debe estar entre %i y %i", minPosWinX, maxPosWinX);
            return -1;
        }
        if(posWinY > maxPosWinY || posWinY < minPosWinY) {
            ofLog(OF_LOG_ERROR, "el argumento posWinY debe estar entre %i y %i", minPosWinY, maxPosWinY);
            return -1;
        }
    }

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, resWidth, resHeight, OF_WINDOW);			// <-------- setup the GL context
    ofSetWindowPosition(posWinX, posWinY);

    window.setWindowTitle("Vmt Node");

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new VmtNode());

}


    string nodeName = "noname";

