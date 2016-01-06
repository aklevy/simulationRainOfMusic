#ifndef PARAMETER_H
#define PARAMETER_H

#include "ofMain.h"
#include "network.hpp"

using namespace OSSIA;
using namespace std;

template <class DataValue,class OSSIAValue>
class Parameter : public ofParameter<DataValue>{
private:
    std::shared_ptr<Node> _botNode;
    std::shared_ptr<Address> _address;
public:
    Parameter(){}

    Parameter(shared_ptr<Node> parentBotNode,
              OSSIAValue ossiaData,
              string name,
              DataValue min,
              DataValue max):
        ofParameter<DataValue>(name,ossiaData.value,min,max),
        _botNode(parentBotNode){

        //this->set(name,data.value);
        // _data = data;
        //creates node
        std::shared_ptr<Node> node = *(_botNode->emplace(_botNode->children().cend(), name));

        //set value
        _address = node->createAddress(ossiaData.getType());
        _address->pushValue(&ossiaData);

        // adds listener to listen to the gui
        this->addListener(this,&Parameter::listen);


    }

    std::shared_ptr<Address> getAddress() const{
        return _address;
    }


    void getValueCallback(const Value * v){
        OSSIAValue * val= (OSSIAValue *)v;
        //ofParameter<DataValue>::set(&(val->value));
        //update(val);
        this->set(val->value);
    }


    void listen(DataValue &data){
        this->set(data);
    }

    /*  void listen(DataValue &data){ // to be checked
        // update the value
        _address->pullValue();

        // get the value
        DataValue * val= (DataValue *)_address->getValue();
        this->set(val->value);
        std::cout << std::to_string(this->get().value) <<std::endl;
        std::cout << " et " <<std::to_string(data.value) <<std::endl;

    }
*/
    void update(OSSIAValue other){
        // change attribute value
        this->set(other.value);
        // update the changed attribute value
        _address->pushValue(&other);
    }
};

#endif // PARAMETER_H
