#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    //Initialisation de la zone grid
    _zoneDim = ofVec3f(600,400,400);
    _zoneGrid = new ZoneGrid(_zoneDim);

    // Initialization of robot
/*    _robotVec = new std::vector<Robot>;

   Robot * _robot = new Metabot(30,_zoneGrid->dimension(),1);
    _robot->initialPosition(ofVec3f(0,0,0));

    _robotVec->push_back(*_robot);
  */  //_robot2 = new Metabot(30,_zoneGrid->dimension(),2);
    //_robot2->initialPosition(ofVec3f(100,200,300));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    _cam.begin();

    ofBackground(0);


    // Draw axes and grid
    _zoneGrid->drawAxes();
    _zoneGrid->drawGrid();

    /*
     * Draw bot defined in setup()
     * Point(0,0,0) is at the back left corner
    */
/*   if(move1){
        move1 = _robot->updatePosition(ofVec3f(1,0,0));
    }
    _robot->drawBot();

    if(move2){
        move2 = _robot2->updatePosition(ofVec3f(0,1,0));
    }
    _robot2->drawBot();
 */
 // Draw zone defined in setup()

    _zoneGrid->drawZone();


    _cam.end();

    ofDrawBitmapStringHighlight(_msg, 10, 20);

}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   _zoneGrid->modifyAxis(key);
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

  /*  unsigned char pixels[3];
    glReadPixels(mouseX,ofGetHeight()-mouseY,1,1,GL_RGB,GL_UNSIGNED_BYTE,pixels);
    string botSelected;

    botSelected = _robot1->isSelected(ofVec3f(pixels[0],pixels[1],pixels[2]));
    if(botSelected != "nothing"){
        _msg = "Robot selected:" + botSelected+"\n";
    }
*/
    /*   //  std::cout << std::to_string(x)<< " "<< std::to_string(y)<<std::endl;

    string botSelected = _robot->isSelected(_cam.screenToWorld(ofVec3f(x,y,_cam.getImagePlaneDistance())));
    _msg = "Robot selected: " + botSelected + "\n";*/
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
