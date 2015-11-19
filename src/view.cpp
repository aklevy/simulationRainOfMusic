#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}

//--------------------------------------------------------------

void View::drawBot(Metabot& meta){
    string model = meta.model();
    ofVec3f position = meta.position();
    ofVec3f color = meta.color();
    int size = meta.size().x;

    if(model == "Square"){
        // Check if the position was valid or not
        if(!checkPosition(position,size)){
            meta.outOfZone();
            //std::cout << "Robot out of the zone" <<std::endl;
        }

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
    else{
        std::cout << "There is not such 3d model, only square for the moment" <<std::endl;
    }
}

bool View::checkPosition(ofVec3f pos, int size){

    for(int i=0;i<3;i++){
        ofVec3f t = pos;
        ofVec3f squareSize = ofVec3f(size);

        //if the bot is out of bound
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
            paintRed(t,squareSize,size);
            return false;
        }
    }
    return true;

}

void View::paintRed(ofVec3f t, ofVec3f squareSize, int size){

    ofPushStyle();
    ofPushMatrix();

    ofTranslate(ofVec3f(size/2) - _zoneDim/2);
    ofTranslate(t);
    ofSetColor(255,0,0); //red
    ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

    ofPopMatrix();
    ofPopStyle();

}
