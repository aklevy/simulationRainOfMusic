#pragma once

#include <thread>
#include "ofxGui.h"
//#include "MSAPhysics3D.h"


#include "ofMain.h"
#include "view.hpp"
#include "zonegrid.hpp"
#include "metabot.hpp"
#include "drone.hpp"
#include "network.hpp"

class ofApp : public ofBaseApp{
public:
    ofApp ();
    ~ofApp () {_nw.setSimRunning(false);}
    void setup();
    void update();
    void draw();


    // Updates one robot
    template<typename Bot_T>
    void updateOneBot(Bot_T& bot){

        // move all the bots to their initial position
        if(_reset){
            bot.reset();
            start = (int)ofGetElapsedTimeMicros()*pow(10,-6);
        }

        if(_play){

            //get the time when the play button is pressed
            if(start == 0){
                start = (int)ofGetElapsedTimeMicros()*pow(10,-6);
            }

            // if bot is in zone update position and  the choeragraphy is on play
            if(bot.isInZone()){
                // test without i-score
                /*  if(bot.id() == 1)
                    bot.move(ofVec3f(3,0,1));
                // the speed is updated automatically as an attribute of the robot
                else
                    bot.move(ofVec3f(-1,0,0.5));
                */
                bot.move();
            }


            // Checks if the position is not out of the zone
            if(bot.isInZone()&& !_view.checkPosition(bot.position(),bot.size(),bot.modelName())){
                //std::cout << "Robot "<< bot.className()<< " "<< bot.id() <<" out of the zone" <<std::endl;
                _warning = "Warning: Out of zone for the robot "
                        + bot.className() + " " + std::to_string(bot.id())
                        + "\n ";

                bot.outOfZone();
                _play.set(false); //stop playing once a robot is out of zone
            }
        }

        // Updates the message to be displayed
        if(bot.color() == _pixel){ //&& _msg.empty()){
            _msg = bot.info();
        }

        // if collision detected
        if(bot.isInCollision() && _warning.empty()){
            _warning = "Warning: First collision detected for the "
                    + bot.className() + " " + std::to_string(bot.id())
                    + "\n at position ("
                    + std::to_string((int)bot.position().x)+", "
                    + std::to_string((int)bot.position().y)+", "
                    + std::to_string((int)bot.position().z)+") \n";
            _play.set(false); //stop playing once a collision is detected
        }
    }
    //Check collision
    template<typename Bot_T,typename OtherBot_T>
    void checkCollision(Bot_T &bot, OtherBot_T &otherbot){
        if(bot.className() != otherbot.className() && !otherbot.isInCollision()){
            if(_view.detectCollision(bot.position(),bot.size(),
                                     otherbot.position(),otherbot.size())){
                bot.collision();
            }
        }
        else if(bot.id() != otherbot.id() && !otherbot.isInCollision()){
            if(_view.detectCollision(bot.position(),bot.size(),
                                     otherbot.position(),otherbot.size())){
                bot.collision();
            }
        }
    }

    // Draws one bot
    template<typename Bot_T>
    void drawOneBot(Bot_T& bot){
        // Checks if the bot is not ouf of zone
        if(!bot.isInZone()){
            _view.paintRed(bot.position(),bot.size(),bot.modelName());
        }
        _view.drawBot(bot.position(),bot.color(),bot.size(),bot.modelName(),bot.loader());
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

    // list containing Metabot
    std::list<Metabot>  _metabots; // no need to initialize

    // list containing Metabot
    std::list<Drone>  _drones;

    // Pixel of where the mouse clicked
    ofVec3f _pixel;

    // Network for communication
    Network _nw;

    // GUI
    ofxPanel _guiViz,_guiSim;

    // Boolean for the stop/play the choeregraphy
    Parameter<bool> _play;
    ofxButton _reset;

    // Probability of losing network packets in %
    Parameter<float> _proba ;// default to  10%

    // Time to start
    int start = 0;

   // msa::physics::World3D _physics;
};

