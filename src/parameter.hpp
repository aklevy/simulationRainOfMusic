#ifndef PARAMETER_H
#define PARAMETER_H

#include "ofMain.h"
#include "network.hpp"

using namespace OSSIA;
using namespace std;

template <class DataValue>
class Parameter : public ofParameter<DataValue>{
private:
    string _name;
    std::shared_ptr<Node> _botNode;
    std::shared_ptr<Address> _address;
public:
    Parameter(){}

    Parameter(shared_ptr<Node> parentBotNode,
              Value::Type type,
              DataValue data,
              string name,
              bool listening):
        ofParameter<DataValue>(data),
        _name(name),
        _botNode(parentBotNode){

        //creates node
        std::shared_ptr<Node> node = *(_botNode->emplace(_botNode->children().cend(), name));

        //set value
        _address = node->createAddress(type);
        _address->pushValue(&data);

        /*if(listening){
            // add listener to listen to i-score
            _address->addCallback([](const Value *v){
                DataValue * val= (DataValue *)v;
                set(val->value)
            });//getValueCallback);
        }*/

        // add listener to listen to the gui
        this->addListener(this,&Parameter::listen);
    }

    void getValueCallback(const Value * v){
        DataValue * val= (DataValue *)v;
        //ofParameter<DataValue>::set(&(val->value));
        //update(val);
        this->set(val->value);
    }

    void listen(DataValue &data){
        this->set(data.value);
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
    void update(DataValue other){
        // change attribute value
        this->set(other);
        // update the changed attribute value
        _address->pushValue(&other);
    }
};

#endif // PARAMETER_H
