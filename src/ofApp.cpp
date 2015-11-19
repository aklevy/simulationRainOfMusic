#include "ofApp.hpp"

//--------------------------------------------------------------
ofApp::ofApp():
    _zoneDim(600,400,400),
    _zoneGrid(_zoneDim), // no need to write explicitely constructor
    _view(_zoneDim),
    _pixel(0){

}

void ofApp::setup(){
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    // Fill Metabot vector
    _metabots.emplace_back(1,ofVec3f(30)); //construct instead of copy
    // _metabots.back().initialPosition(ofVec3f(0));
    _metabots.emplace_back(2,ofVec3f(50),ofVec3f(100),"metabot.obj"); //construct instead of copy

    // Fill Drone vector
    _drones.emplace_back(1,ofVec3f(10),ofVec3f(0,200,50),"drone.obj"); //construct instead of copy

}
//--------------------------------------------------------------
void ofApp::update(){
    for(auto &metabot : _metabots){
        updateOneBot(metabot);
    }
    for(auto &drone : _drones){
        updateOneBot(drone);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    _cam.begin();

    ofBackground(0);

    // Draw axes and grid
    _zoneGrid.drawAxes();
    _zoneGrid.drawGrid();

    //Draw Metabots
    for(auto &bot : _metabots){
        drawOneBot(bot);
    }

    //Draw Drones
    for(auto &bot : _drones){
        drawOneBot(bot);
    }

    // Draw zone defined in setup()
    _zoneGrid.drawZone();


    _cam.end();
    ofDrawBitmapStringHighlight(_msg, 10, 20);

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _zoneGrid.modifyAxis(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    _msg.clear();

    // Gets pixel value under the mouse
    unsigned char pixels[3];
    glReadPixels(mouseX,ofGetHeight()-mouseY,1,1,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    _pixel = ofVec3f(pixels[0],pixels[1],pixels[2]);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
