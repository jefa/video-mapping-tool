#include <QtGui>
#include "ofMain.h"
#include "vmt.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( int argc, char** argv ) {

    QApplication app(argc, argv); //Qt app

    int resWidth, resHeight, posWinX, posWinY;

    resWidth = 800;
    resHeight = 600;
    posWinX = 20 + 500;
    posWinY = 40;

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, resWidth, resHeight, OF_WINDOW);			// <-------- setup the GL context

    ofSetWindowPosition(posWinX, posWinY);
    window.setWindowTitle("Vmt");

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new Vmt() );

    return app.exec(); //Qt app
}
