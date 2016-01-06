#pragma once

#include <thread>
//#include "ofxGui.h"

#include "ofMain.h"
#include "view.hpp"
#include "zonegrid.hpp"
#include "metabot.hpp"
#include "drone.hpp"
#include "network.hpp"

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
        if(play){
            // if bot is in zone update position and  the choeragraphy is on play
            if(Bool(true) == bot.isInZone()){
                if(bot.id() == 1)
                    bot.move(ofVec3f(3,0,1));
                // bot.move(); the speed is updated automatically as an attribute of the robot
                else
                    bot.move(ofVec3f(-1,0,0.5));
            }

            // Checks if the position is not out of the zone
            if((Bool(true) == bot.isInZone())&& !_view.checkPosition(bot.position(),bot.size().x,bot.modelName())){
                std::cout << "Robot "<< bot.className()<< " "<< bot.id() <<" out of the zone" <<std::endl;
                /* _warning = "The "
                    + bot.className() + " " + std::to_string(bot.id())
                    + " is out of the zone\n";
            */bot.outOfZone();
                play = false; //stop playing once a robot is out of zone
            }
        }
        // Checks if there is a collision
        /*for(auto &bot : _metabots){
                if(bot.id() != otherbot.id() && !otherbot.isInCollision()){
                    if(_view.detectCollision(bot.position(),bot.size(),
                                             otherbot.position(),otherbot.size())){
                        bot.collision();
                    }
                }
                //_view.drawCollisionCircle(otherbot.position(),bot.position(),bot.size());
                /*std::cout << "Collision detected at "+ std::to_string(bot.position().x)
                                                 + " & " + std::to_string(otherbot.position().x)<<std::endl;
     */
        //  }


        // Updates the message to be displayed
        if(bot.color() == _pixel && _msg.empty()){
            _msg = bot.info();
        }

        // if collision detected
        if((Bool(true) == bot.isInCollision()) && _warning.empty()){
            _warning = "Warning: First collision detected for the "
                    + bot.className() + " " + std::to_string(bot.id())
                    + "\n at position ("
                    + std::to_string((int)bot.position().x)+", "
                    + std::to_string((int)bot.position().y)+", "
                    + std::to_string((int)bot.position().z)+") \n";
            play = false; //stop playing once a collision is detected
        }
    }

    // Draws one bot
    template<typename Bot_T>
    void drawOneBot(Bot_T& bot){
        // Checks if the bot is not ouf of zone
        if(Bool(false) == bot.isInZone()){
            _view.paintRed(bot.position(),bot.size().x,bot.modelName());
        }
        /*if(bot.collision()){

        }*/
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


    string _msg,_warning,_msgGeneral;

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

    // Boolean for the stop/play the choeregraphy
    bool play = true;

    // Network for communication
    Network _nw;

    // GUI
 /*   ofxPanel _gui;
    Parameter<Float> _coll;
*/
};
