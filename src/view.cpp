#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}

//--------------------------------------------------------------

bool View::checkPosition(ofVec3f pos, int size,string model){

    for(int i=0;i<3;i++){
        ofVec3f t = pos;
        ofVec3f squareSize = ofVec3f(size);

        //if the bot is out of bound, paint in red the face out
        if ((pos[i] >= _zoneDim[i] - size) || (pos[i] < 0)){
            if (pos[i] >= _zoneDim[i] - size){
                t[i] += size/2;
                //std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            if (pos[i] < 0) {
                t[i] -= size/2;
                // std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            squareSize[i] = 1;

            if (model == "Sphere"){
                sizetmp = 2 * size;
            }
            paintRed(t,squareSize,sizetmp);

            return false;
        }
    }
    return true;

}
void View::paintRed(ofVec3f trans, ofVec3f squareSize, int size){
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(ofVec3f(size/2) - _zoneDim/2);
    ofTranslate(trans);
    ofSetColor(255,0,0); //red
    ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

    ofPopMatrix();
    ofPopStyle();
}


