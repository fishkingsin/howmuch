#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    background.loadImage("background.png");
    grabber.initGrabber(640,480);
    
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    objectFinder.setup("haarcascade_frontalface_alt2.xml");
    objectFinder.setPreset(ObjectFinder::Fast);

    cropped.allocate(150,150, OF_IMAGE_COLOR);
    
    
    //-----------faceRecognizer
    // 0 = Eigenfaces_method ; has much bigger database (.yml). takes longer to load
    // 1 = Fisherfaces_method; faster to load
    // 2 = LBPHFaces_method
    
    //int method_used, int maxFaces, bool bAlreadySavedModel, string folderName
    recognizer.setup(1,132,true,"faces");
    
    cout<<recognizer.getUniquePersonCount()<<" seperate people are in the training database"<<endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew()) {
        objectFinder.update(grabber);
        
        if(objectFinder.size() > 0) {
            cv::Rect roi = toCv(objectFinder.getObject(0));
            Mat camMat = toCv(grabber);
            Mat croppedCamMat(camMat, roi);
            resize(croppedCamMat, cropped);
            cropped.update();
            
            Mat face;
            //recognizer wants grayscale image
            cvtColor(toCv(cropped), face, CV_BGR2GRAY);
            recognizer.update(face);
            
            cout<<"recognizer.getConfidence() "<<recognizer.getConfidence()<<endl;
            predictedPerson = recognizer.getPrediction();
            cout<<"you look most like this peson from the training database "<<predictedPerson<<endl;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    background.draw(0,0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5 - grabber.getWidth()*0.5, ofGetHeight()*0.4 - grabber.getHeight()*0.5);
    grabber.draw(0, 0);
    objectFinder.draw();
    cropped.draw(0 , grabber.getHeight());
    if(objectFinder.size() > 0) recognizer.drawImageOfPerson(predictedPerson, 150,grabber.getHeight(), 150,150 );
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
