#include "robot.h"

Robot::Robot(int size, ofVec3f dimZone):
    _size(size),
    _dimZone(dimZone){
}

Robot::~Robot(){

}

void Robot::initialPosition(ofVec3f initPos = ofVec3f(0,0,0)){
    _position = initPos;
}

//--------------------------------------------------------------

void Robot::drawBot(){

    ofPushStyle();
    ofPushMatrix();
    glDepthMask(false);

    // ofTranslate(_x-dimZone.x/2,_y+_size/2-dimZone.y/2,_z-dimZone.z/2);
    ofTranslate(_size/2 - _dimZone.x/2, _size/2 - _dimZone.y/2,_size/2 - _dimZone.z/2);
    ofTranslate(_position);
    ofSetLineWidth(1);
    ofSetColor(color().x,color().y,color().z);
    // ofSetColor(0,0,255);
    ofFill();
    ofDrawBox(_size);


    ofSetColor(0,0,0);
    ofNoFill();
    ofDrawBox(_size);

    glDepthMask(true);
    ofPopMatrix();
    ofPopStyle();

}

bool Robot::updatePosition(ofVec3f speed){
    ofVec3f nextPos = nextPosition(speed);
    if(checkPosition(nextPos)){
        _position = nextPos;
        return true;
    }
    else{
        std::cout<<"The position of " << botID() << " was not updated"<< std::endl;
    }
    return false;
}

bool Robot::checkPosition(ofVec3f nextPos){
    for(int i=0;i<3;i++){
        if (nextPos[i] >= _dimZone[i] - _size){
            paintRed(i+1);
            std::cout<< botID() << " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            return false;

        }
        if (nextPos[i] < 0) {
            paintRed(-(i+1));
            std::cout<< botID() << " will be out of the zone, check position["<< std::to_string(i) <<"]"<< std::endl;
            return false;
        }
    }
    return true;
}

void Robot::paintRed(int face){

    ofVec3f t = _position;
    if(face < 0 ){
        t[abs(face)-1] -= _size/2;
    }
    else{
        t[abs(face)-1] += _size/2;
    }

    ofVec3f squareSize = ofVec3f(_size);
    squareSize[abs(face)-1] = 1;
    ofPushStyle();
    ofPushMatrix();

    ofTranslate(_size/2 - _dimZone.x/2, _size/2 - _dimZone.y/2,_size/2 - _dimZone.z/2);
    ofTranslate(t);
    ofSetColor(255,0,0); //red

    ofDrawBox(squareSize.x,squareSize.y,squareSize.z);

    ofPopMatrix();
    ofPopStyle();

}

string Robot::isSelected(ofVec3f colorPicked){
    std::cout <<  std::to_string(colorPicked.z)<<std::endl;
    std::cout <<  std::to_string(colorPicked.z)<<std::endl;
    std::cout <<  std::to_string(color().z)<<std::endl;

    if(colorPicked == color()){
        return botID();
    }
    return "nothing";
    /*// Translate the vector select to be in the referential of the zone
    std::cout << std::to_string(colorPicked.x)<< " "<< std::to_string(colorPicked.y)<<std::endl;

    ofVec3f t  = ofVec3f(_size/2 - _dimZone.x/2, _size/2 - _dimZone.y/2,_size/2 - _dimZone.z/2);
    colorPicked -= t;

    std::cout << std::to_string(colorPicked.x)<< " "<< std::to_string(colorPicked.y)<<std::endl;
    std::cout << std::to_string(_position.x)<< " "<< std::to_string(_position.y)<<std::endl;

    int epsilon = 100;
    if(colorPicked.x  < (_position.x + _size + epsilon) &&  colorPicked.x > (_position.x - epsilon)
            && colorPicked.y  <(_position.y + _size + epsilon) && colorPicked.y > (_position.y -epsilon) ){
        return botID();
    }
    return "nothing";*/
}

