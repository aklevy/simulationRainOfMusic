#include "ofApp.hpp"

//--------------------------------------------------------------
ofApp::ofApp():
    _zoneDim(600,400,400),
    _zoneGrid(_zoneDim), // no need to write explicitely constructor
    _view(_zoneDim),
    _pixel(0),
    _nw(){
}

void ofApp::setup(){
    // To print out log, uncomment the line below
    // ofSetLogLevel(OF_LOG_VERBOSE);

    // To change the frame rate, uncomment the line below
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other
    ofEnableDepthTest();

    // Fill Metabot vector
    _metabots.emplace_back(1, _nw.getSceneNode()); //construct instead of copy
    //_metabots.emplace_back(2,ofVec3f(40),ofVec3f(100,0,50));

    // Example for 3D model : warning : slows down the app
    _metabots.emplace_back(3, _nw.getSceneNode(),ofVec3f(40),ofVec3f(400,0,50),"/opt/of_v0.9.0_linux64_release/apps/myApps/simulationRainOfMusic/bin/data/spider.obj"); //construct instead of copy
    if( !_metabots.back().load()){
        std::cout << "The 3D object "<<_metabots.back().modelName()<< " was not loaded correctly"<<std::endl;
    }

    // Fill Drone vector
   // _drones.emplace_back(1,_nw.getSceneNode(),ofVec3f(10),ofVec3f(0,200,50)); //construct instead of copy
}

//--------------------------------------------------------------
void ofApp::update(){

    for(auto &metabot : _metabots){
        updateOneBot(metabot);
        //metabot.test();
        metabot.updateBot();
    }
    for(auto &drone : _drones){
        updateOneBot(drone);
        drone.updateBot();
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

    // Check collision
    for(auto &bot : _metabots){
        for(auto &otherbot : _metabots){
            if(bot.id() != otherbot.id() && otherbot.isInCollision()==Bool(false)){
                if(_view.detectCollision(bot.position(),bot.size(),
                                         otherbot.position(),otherbot.size())){
                    bot.collision();
                }
            }
            // _view.drawCollisionCircle(otherbot.position(),bot.position(),bot.size());
            /*std::cout << "Collision detected at "+ std::to_string(bot.position().x)
                                             + " & " + std::to_string(otherbot.position().x)<<std::endl;
 */
        }

    }

    // Draw zone defined in setup()
    _zoneGrid.drawZone();

    _cam.end();

    // Displays the message concerning selected robot
    ofDrawBitmapStringHighlight(_msg, 10, 20);

    // Displays warning messages
    ofDrawBitmapStringHighlight(_warning, ofGetWidth()/2, 20);

    // Displays general message (=time)
    if(play){
        _msgGeneral.clear();
        _msgGeneral = "Time : "+ std::to_string((int)ofGetElapsedTimeMicros()*pow(10,-6))+"\n";
    }
    ofDrawBitmapStringHighlight(_msgGeneral, 10, ofGetHeight()-20);

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
    /*  ofVec3f mouse;
    mouse.x = x;
    mouse.y = y;
    glReadPixels(mouse.x, ofGetHeight()-1-mouse.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouse.z);
    ofVec3f mousePos = _cam.screenToWorld(ofVec3f(x,-y,1));//_cam.getDistance()));
    std::cout << std::to_string(mousePos.x  -600)<< " "<<  std::to_string(mousePos.y-400)<< " "<<  std::to_string(mousePos.z-400) <<std::endl;
*/
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
