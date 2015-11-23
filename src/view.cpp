#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}
//--------------------------------------------------------------
void View::drawBot(const ofVec3f position,const ofVec3f color, const int size, string modelName,ofxAssimpModelLoader model) {

    ofPushStyle();
    ofSetColor(color.x,color.y,color.z);
    ofFill();
    ofSetLineWidth(1);

    ofPushMatrix();
    glDepthMask(false);
    //std::cout << modelName<<std::endl;
    if(string::npos == modelName.find("obj")){
        // std::cout << modelName<<std::endl;
        ofTranslate(ofVec3f(size/2) - _zoneDim/2);
        ofTranslate(position);

        if(modelName == "Square"){
            ofDrawBox(size);

            ofSetColor(0,0,0);
            ofNoFill();
            ofDrawBox(size);
        }
        else if(modelName == "Sphere"){
            ofDrawSphere(size);
        }
    }
    else{
        std::cout << modelName<<std::endl;

        draw3dObject(position,size,modelName,model);

    }

    //std::cout << std::to_string(_model.getPosition().x)<<std::endl;

    glDepthMask(true);
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void View::draw3dObject(const ofVec3f position, const int size, string modelName, ofxAssimpModelLoader model){
    // Load 3d object


    // translation
    ofTranslate(ofVec3f(size/2) - _zoneDim/2);
    //ofTranslate(position);

    // Draw
    ofTranslate(ofVec3f(0,-55,0));
    model.setPosition(position.x,position.y,position.z);
    model.drawFaces();

    std::cout << std::to_string(model.getPosition().x)<<std::endl;

}
//--------------------------------------------------------------

bool View::checkPosition(ofVec3f pos, int size,string model){
    for(int i=0;i<3;i++){
        ofVec3f trans = pos;
        ofVec3f squareSize = ofVec3f(size);

        //if the bot is out of bound, paint in red the face out
        if ((pos[i] >= _zoneDim[i] - size) || (pos[i] < 0)){
            if (pos[i] >= _zoneDim[i] - size){
                trans[i] += size/2;
                //std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            if (pos[i] < 0) {
                trans[i] -= size/2;
                // std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            squareSize[i] = 1;

            paintRed(trans,squareSize,size,model);

            return false;
        }
    }
    return true;

}
void View::paintRed(ofVec3f trans, ofVec3f squareSize, int size,string model){
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(trans);

    if (model == "Sphere"){
        ofVec3f t(-size/2);
        for(int i=0;i<3;i++){
            if(squareSize[i] == 1){
                t[i] = 0;
            }
        }
        ofTranslate(ofVec3f(t));
        size= 2 * size;
    }

    ofTranslate(ofVec3f(size/2) - _zoneDim/2);

    ofSetColor(255,0,0); //red
    ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

    ofPopMatrix();
    ofPopStyle();
}


