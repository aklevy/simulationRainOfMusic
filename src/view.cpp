#include "view.hpp"

View::View(ofVec3f zoneDim):
    _zoneDim(zoneDim){
}
//--------------------------------------------------------------
void View::drawBot(const ofVec3f position,const ofVec3f color, const ofVec3f size, const string& modelName, ofxAssimpModelLoader& model) {

    ofPushStyle();
    ofSetColor(color.x,color.y,color.z);
    ofFill();
    ofSetLineWidth(1);

    ofPushMatrix();
    glDepthMask(false);
    //std::cout << modelName<<std::endl;
    if(string::npos == modelName.find("obj")){
        // std::cout << modelName<<std::endl;
        ofTranslate(size/2 - _zoneDim/2);
        ofTranslate(position);

        if(modelName == "Square"){
            ofDrawBox(size.x,size.y,size.z);

            ofSetColor(0,0,0);
            ofNoFill();
            ofDrawBox(size.x,size.y,size.z);
        }
        else if(modelName == "Sphere"){
            ofDrawSphere(size.x);
        }
    }
    else{
        // std::cout << modelName<<std::endl;

        draw3dObject(position,size,modelName,model);

    }

    //std::cout << std::to_string(_model.getPosition().x)<<std::endl;

    glDepthMask(true);
    ofPopMatrix();
    ofPopStyle();
}
//--------------------------------------------------------------

void View::draw3dObject(const ofVec3f position, const ofVec3f size, const string& modelName, ofxAssimpModelLoader& model){
    // Load 3d object

    // translation
    ofTranslate(size/2 - _zoneDim/2);
    //ofTranslate(position);

    // Draw
    ofTranslate(ofVec3f(0,-size.y/2,0));
    model.setPosition(position.x,position.y,position.z);
    model.drawFaces();
}
//--------------------------------------------------------------

bool View::checkPosition(ofVec3f pos, ofVec3f size,string model){
    for(int i=0;i<3;i++){
        //if the bot is out of bound, return true
        if ((pos[i] >= _zoneDim[i] - size[i]) || (pos[i] < 0)){

            return false;
        }
    }
    return true;
}
//--------------------------------------------------------------

void View::paintRed(ofVec3f pos, ofVec3f size, string model){
    for(int i=0;i<3;i++){
        ofVec3f trans = pos;
        ofVec3f squareSize = size;

        //if the bot is out of bound, return true
        if ((pos[i] >= _zoneDim[i] - size[i]) || (pos[i] < 0)){
            if (pos[i] >= _zoneDim[i] - size[i]){
                trans[i] += size[i]/2;
                //std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            if (pos[i] < 0) {
                trans[i] -= size[i]/2;
                // std::cout<<  " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            }
            squareSize[i] = 1;

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

            ofTranslate(size/2 - _zoneDim/2);

            ofSetColor(255,0,0); //red
            ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

            ofPopMatrix();
            ofPopStyle();
            break;
        }
    }
}

bool View::detectCollision(ofVec3f pos, ofVec3f size, ofVec3f otherPos, ofVec3f otherSize)
{
    float dist = pos.distance(otherPos) - MAX(size.x,MAX(size.y,size.z))/2 - MAX(otherSize.x,MAX(otherSize.y,otherSize.z))/2;//sqrt(2)/2*(size.x + otherSize.x);//distance - radius of bounding sphere
    if (dist < size.x+2){
        pos.middle(otherPos);
        //ofVec3f middle = (pos+otherPos)/2;//pos+dist/2;
        drawCollisionCircle(pos,size);
        return true;
    }
    return false;
}

//--------------------------------------------------------------

void View::drawCollisionCircle(  const ofVec3f& position, const ofVec3f size){

    ofPushMatrix();
    ofTranslate(size/2 - _zoneDim/2);
    ofPushStyle();
    ofSetColor(255,0,0);
    //  ofSpherePrimitive sphere;
    // sphere.setRadius(size/2);
    //sphere.move(ofVec3f(size/2) - _zoneDim/2);
    //std::cout << std::to_string(position.x)<<" "<< std::to_string(position.z)<<std::endl;
    // sphere.setPosition(position);
    //  of3dGraphics::drawSphere(position,size/2);
    // sphere.draw();
    ofNoFill();
    ofDrawCircle(position,size.x);
    ofPopStyle();
    ofPopMatrix();

    //    ofTranslate(ofVec3f(size/2) - _zoneDim/2);

}


