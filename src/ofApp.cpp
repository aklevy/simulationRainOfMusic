#include "ofApp.hpp"

//--------------------------------------------------------------
ofApp::ofApp():
   _zoneDim(1200,500,800), // 12m x 5m x 8m
    _zoneGrid(_zoneDim), // no need to write explicitely constructor
    _view(_zoneDim),
    _pixel(0),
    _nw(){
}

ofApp::~ofApp () {
    _nw.setSimRunning(false);
    _play.removeListener(&_play,&Parameter<bool>::listen);
    _proba.removeListener(&_proba,&Parameter<float>::listen);
}


void ofApp::setup(){
    // To print out log, uncomment the line below
    //ofSetLogLevel(OF_LOG_VERBOSE);

    // To change the frame rate, uncomment the line below
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    // this uses depth information for occlusion
    // rather than always drawing things on top of each other


    //   ofEnableDepthTest();
    /*
     *  GUI
     * */
    _guiSim.setup("Simulation");
    _guiSim.setPosition( ofGetWidth()- 200,80);
    _guiSim.add(_proba.setup(_nw.getSceneNode(),"PacketLoss",10,0,100));
    _proba.getAddress()->addCallback([&](const Value *v){
        Float * val= (Float *)v;
        if(val->value != _proba){
            _proba.set(val->value);
        }
    });
    _proba.addListener(&_proba,&Parameter<float>::listen);


    // GUi panel for robots
    _guiViz.setup("Robots");
    _guiViz.setPosition(10,80);

    //_play.setup(_nw.getSceneNode(),"play",false);

    // i-score listener
    _guiViz.add(_play.setup(_nw.getSceneNode(),"play",false));

    _play.getAddress()->addCallback([&](const Value *v){
        Bool * val= (Bool *)v;
        if(val->value != _play){
            _play.set(val->value);
        }
    });
    _play.addListener(&_play,&Parameter<bool>::listen);

    // gui listener
    _guiViz.add(_reset.setup("reset"));


    // Fill Metabot list
    _metabots.emplace_back(1, _nw.getSceneNode(),_zoneDim,_proba.get()); //construct instead of copy
    //_metabots.emplace_back(2,ofVec3f(40),ofVec3f(100,0,50));
    _metabots.emplace_back(2, _nw.getSceneNode(),_zoneDim,_proba.get(),ofVec3f(200,0,50),ofVec3f(10),"data/spider.obj");
    if( !_metabots.back().load()){
        std::cout << "The 3D object "<<_metabots.back().modelName()<< " was not loaded correctly"<<std::endl;
    }
    // Example for 3D model
    _metabots.emplace_back(3, _nw.getSceneNode(),_zoneDim,_proba.get(),ofVec3f(400,0,50),ofVec3f(10),"data/spider.obj"); //construct instead of copy
    if( !_metabots.back().load()){
        std::cout << "The 3D object "<<_metabots.back().modelName()<< " was not loaded correctly"<<std::endl;
    }

    // Fill Drone list
    _drones.emplace_back(1,_nw.getSceneNode(),_zoneDim,_proba.get(),ofVec3f(0,200,50)); //construct instead of copy

    // Adding robots to the GUI
    for(auto &metabot : _metabots){ //template bot
        //metabot.setup();
        _guiViz.add(metabot.parameters());
        _guiSim.add(metabot.simulation());
    }

    for(auto &drone : _drones){ //template bot
        _guiViz.add(drone.parameters());
        _guiSim.add(drone.simulation());
    }

    // collapse all tabs
    _guiViz.minimizeAll();
    _guiSim.minimizeAll();

}

//--------------------------------------------------------------
void ofApp::update(){

    for(auto &metabot : _metabots){
        updateOneBot(metabot);
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
    _zoneGrid.drawGraduation();

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
            checkCollision(bot,otherbot);
        }
    }
    for(auto &bot : _drones){
        for(auto &otherbot : _metabots){
            checkCollision(bot,otherbot);
        }
        for(auto &otherbot : _drones){
            checkCollision(bot,otherbot);
        }
    }
    // Draw zone defined in setup()
    _zoneGrid.drawZone();


    // Displays the graduation
     ofVec3f pos0 = _cam.worldToScreen(_zoneDim);
    //ofDrawBitmapStringHighlight("(0,0,0)", pos0.x, pos0.y);

    _cam.end();

    // GUI
    /*
    _gui.setTextColor(ofColor(255));
    _gui.setBackgroundColor(ofColor(255));
    _gui.setFillColor(255);
    _gui.setBorderColor(255);
   */
    _guiSim.draw();
    _guiViz.draw();

    // Displays the message concerning selected robot
    ofDrawBitmapStringHighlight(_msg, 10, 20);

    // Displays warning messages
    ofDrawBitmapStringHighlight(_warning, ofGetWidth()/2, 20);

    // Displays general message (=time)
    if(_play.get()){
        _msgGeneral.clear();
        _msgGeneral = "Time : "+ std::to_string((int)ofGetElapsedTimeMicros()*pow(10,-6)-start)+"\n";
    }
    ofDrawBitmapStringHighlight(_msgGeneral, 10, ofGetHeight()-20);

    // Displays help message
    if(_help){
        string helpmsg = string("Press 'h' to hide this help message \n"
                                "Press 'g' to toggle graduation \n"
                                "Press 'x', 'y' or 'z'to toggle axes \n");
     ofDrawBitmapStringHighlight(helpmsg,ofGetWidth()/2, ofGetHeight() -100);
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _zoneGrid.modifyAxis(key);
    // display help message
    if(key == 'h'){
        _help = !_help;
    }
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
