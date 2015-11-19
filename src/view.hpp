#ifndef VIEW_H
#define VIEW_H

#include "ofMain.h"
#include "metabot.hpp"

class BotDuPlop
{
public :
    std::string model() const
    { return {}; }
    ofVec3f position() const
    { return {}; }
    ofVec3f color() const
    { return {}; }
    ofVec3f size() const
    { return {}; }
};

class View
{
public:
    explicit View(ofVec3f zoneDim); // avoids implicit conversion ofVec3f->View

    // Draws the Metabot given

    template<typename Bot_T>
    void drawBot(const Bot_T& meta){
        string model = meta.model();
        ofVec3f position = meta.position();
        ofVec3f color = meta.color();
        int size = meta.size().x;

        if(model == "Square"){


            ofPushStyle();
            ofPushMatrix();
            glDepthMask(false);

            ofTranslate(ofVec3f(size/2) - _zoneDim/2);
            ofTranslate(position);
            ofSetLineWidth(1);

            ofSetColor(color.x,color.y,color.z);
            ofFill();
            ofDrawBox(size);

            ofSetColor(0,0,0);
            ofNoFill();
            ofDrawBox(size);

            glDepthMask(true);
            ofPopMatrix();
            ofPopStyle();
        }
    }

    // Checks if the robot is out of the zone
    // if out of zone, changes the face out color to red
    bool checkPosition(ofVec3f pos, int size);

    // Returns the information message contaning the given Metabot's data
    string information(Metabot &bot);

private:
    // choregraphy zone dimension
    ofVec3f _zoneDim;


};

#endif //VIEW_H
