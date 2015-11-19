#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}

//--------------------------------------------------------------



bool View::checkPosition(ofVec3f pos, int size){

    for(int i=0;i<3;i++){
        ofVec3f t = pos;
        ofVec3f squareSize = ofVec3f(size);

        //if the bot is out of bound, paint in red the face out
        if ((pos[i] >= _zoneDim[i] - size) || (pos[i] < 0)){
            if (pos[i] >= _zoneDim[i] - size){
                t[i] += size/2;
                // std::cout<< botID() << " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            if (pos[i] < 0) {
                t[i] -= size/2;
                // std::cout<< botID() << " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            squareSize[i] = 1;

            ofPushStyle();
            ofPushMatrix();

            ofTranslate(ofVec3f(size/2) - _zoneDim/2);
            ofTranslate(t);
            ofSetColor(255,0,0); //red
            ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

            ofPopMatrix();
            ofPopStyle();

            return false;
        }
    }
    return true;

}

string View::information(Metabot &bot){
    string msg;

    msg = "Robot selected:"
            + bot.className() + " "
            + std::to_string( bot.id()) + "\n";
    msg += "at position ("
            + std::to_string((int)bot.position().x)+", "
            + std::to_string((int)bot.position().y)+", "
            + std::to_string((int)bot.position().z)+") ";

    return msg;
}

