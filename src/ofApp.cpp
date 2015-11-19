#include "ofApp.hpp"

//--------------------------------------------------------------
ofApp::ofApp():
    _zoneDim(600,400,400),
    _zoneGrid(_zoneDim), // no need to write explicitely constructor
    _view(_zoneDim){

}

void ofApp::setup(){
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    _metabots.emplace_back(_zoneGrid.dimension(),ofVec3f(30),1); //construct instead of copy
    // _metabots.back().initialPosition(ofVec3f(0));
    _metabots.emplace_back(_zoneGrid.dimension(),ofVec3f(50),2,ofVec3f(100),"Metabot.obj"); //construct instead of copy
}

//--------------------------------------------------------------
void ofApp::update(){
    for(auto &bot : _metabots){

        // Checks if the 3D model object is available
        if(bot.model() != "Square"){
            std::cout <<"The 3D model '"<< bot.model() <<"' for the robot "<<bot.className()<< " "<< bot.id() << " was not found : the robot will be displayed as a square instead" <<std::endl;
            bot.defaultModel();
        }

        // Checks if the position is not out of the zone
        if(bot.isInZone() && !_view.checkPosition(bot.position(),bot.size().x)){
            std::cout << "Robot "<< bot.className()<< " "<< bot.id() <<" out of the zone" <<std::endl;
            bot.outOfZone();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    _cam.begin();

    ofBackground(0);

    // Draw axes and grid
    _zoneGrid.drawAxes();
    _zoneGrid.drawGrid();

    //Draw bot defined in setup()
    for(auto &bot : _metabots){
        if(bot.isInZone()){
            bot.move(ofVec3f(1,0,0));
        }
        _view.drawBot(bot);
        if(bot.id() == _selectedId){
            _msg = _view.information(bot);
        }
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
    ofVec3f pix(pixels[0],pixels[1],pixels[2]);


    for(auto &bot : _metabots){
        if(bot.color() == pix){
            _selectedId = bot.id();
            break;
        }
    }


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
