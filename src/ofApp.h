#pragma once

#include "ofMain.h"
#ifdef USE_KINECT
#include "ofxKinect.h"
#endif
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxFaceRecognizer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    ofImage background;
#ifdef USE_KINECT
    ofxKinect kinect;
#else
    ofVideoGrabber grabber;
#endif
    ofxCv::ObjectFinder objectFinder;
    ofImage cropped;
    ofxFaceRecognizer recognizer;
    int predictedPerson;

		
};
