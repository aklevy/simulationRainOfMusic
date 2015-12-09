#pragma once

#include "ofMain.h"
#include "view.hpp"
#include "zonegrid.hpp"
#include "metabot.hpp"
#include "drone.hpp"

class ofApp : public ofBaseApp{
public:
    ofApp ();
    void setup();
    void update();
    void draw();

    // Updates one robot
    template<typename Bot_T>
    void updateOneBot(Bot_T& bot){

        // Checks if the 3D model object is available
        /*if(bot.model() != bot.defaultModel()){
            std::cout <<"The 3D model '"<< bot.model()
                     <<"' for the robot "<<bot.className() << " "<< bot.id()
                    << " was not found : the robot will be displayed as a "
                    << bot.defaultModel() <<" instead" <<std::endl;
            bot.modelToDefault();
            //    std::cout << bot.model()<<std::endl;
        }*/

        // Checks if the position is not out of the zone
        if(bot.isInZone() && !_view.checkPosition(bot.position(),bot.size().x,bot.modelName())){
            std::cout << "Robot "<< bot.className()<< " "<< bot.id() <<" out of the zone" <<std::endl;
            bot.outOfZone();
        }

        // Updates the message to be displayed
        if(bot.color() == _pixel){
            _msg = bot.info();
        }

    }

    // Draws one bot
    template<typename Bot_T>
    void drawOneBot(Bot_T& bot){
        // Checks if the bot is not ouf of zone
        if(bot.isInZone()){
            bot.move(ofVec3f(3,0,1));
        }
        else{
            _view.checkPosition(bot.position(),bot.size().x,bot.modelName());
        }
        _view.drawBot(bot.position(),bot.color(),bot.size().x,bot.modelName(),bot.loader());
    }


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

    // Vector containing Metabot
    std::vector<Drone>  _drones;

    // Pixel of where the mouse clicked
    ofVec3f _pixel;

};
