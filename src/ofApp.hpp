#pragma once

#include "ofMain.h"
#include "view.hpp"
#include "zonegrid.hpp"
#include "metabot.hpp"


class ofApp : public ofBaseApp{
public:
    ofApp ();
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);


    string _msg;

private:
    // Camera
    ofEasyCam _cam;

    // Zone with grid
    ofVec3f _zoneDim;
    ZoneGrid _zoneGrid;

    // View
    View _view;

    // Vector containing Metabot
    std::vector<Metabot>  _metabots; // no need to initialize



};
