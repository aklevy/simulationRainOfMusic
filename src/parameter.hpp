#ifndef PARAMETER_H
#define PARAMETER_H

#include "ofMain.h"
#include "network.hpp"

template<typename> struct MatchingType;

template<> struct MatchingType<float> {
    using ofx_type = float;
    using ossia_type = OSSIA::Float;
    static constexpr const auto val = OSSIA::Value::Type::FLOAT;
    static ofx_type convertFromOssia(Value* v) {
        ossia_type * f = (ossia_type *)v;
        return f->value; }
    static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<double> {
    using ofx_type = double;
    static constexpr const auto val = OSSIA::Value::Type::FLOAT;
    using ossia_type = OSSIA::Float;

    static ofx_type convertFromOssia(Value* v) {
        ossia_type * f = (ossia_type *)v;
        return f->value; }
    static ossia_type* convert(ofx_type f) { return new ossia_type{float(f)}; }
};
template<> struct MatchingType<int> {
    using ofx_type = int;
    static constexpr const auto val = OSSIA::Value::Type::INT;
    using ossia_type = OSSIA::Int;

    static ofx_type convertFromOssia(Value* v) {
        ossia_type * f = (ossia_type *)v;
        return f->value; }
    static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<bool> {
    using ofx_type = bool;
    static constexpr const auto val = OSSIA::Value::Type::BOOL;
    using ossia_type = OSSIA::Bool;

    static ofx_type convertFromOssia(Value* v) {
        ossia_type * f = (ossia_type *)v;
        return f->value; }
    static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};

template<> struct MatchingType<string> {
    using ofx_type = std::string;
    static constexpr const auto val = OSSIA::Value::Type::STRING;
    using ossia_type = OSSIA::String;

    static ofx_type convertFromOssia(Value* v) {
        ossia_type * f = (ossia_type *)v;
        return f->value; }
    static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<ofVec3f> {
    using ofx_type = ofVec3f;
    static constexpr const auto val = OSSIA::Value::Type::TUPLE;
    using ossia_type = OSSIA::Tuple;

    static ofx_type convertFromOssia(ossia_type t) {
        float x = ((OSSIA::Float*)t.value[0])->value;
        float y = ((OSSIA::Float*)t.value[1])->value;
        float z = ((OSSIA::Float*)t.value[2])->value;

        t.value.clear();
        return ofx_type(x,y,z);
    }
    static ossia_type* convert(ofx_type f) {
        auto tuple = new ossia_type;
        tuple->value.reserve(3);
        tuple->value.push_back(new OSSIA::Float(f.x));
        tuple->value.push_back(new OSSIA::Float(f.y));
        tuple->value.push_back(new OSSIA::Float(f.z));
        return tuple;
    }
};
template<> struct MatchingType<ofVec2f> {
    using ofx_type = ofVec2f;
    static constexpr const auto val = OSSIA::Value::Type::TUPLE;
    using ossia_type = OSSIA::Tuple;

    static ofx_type convertFromOssia(ossia_type t) {
        float x = ((OSSIA::Float*)t.value[0])->value;
        float y = ((OSSIA::Float*)t.value[1])->value;
        t.value.clear();
        return ofx_type(x,y);

    }
    static ossia_type* convert(ofx_type f) {
        auto tuple = new ossia_type;
        tuple->value.reserve(2);
        tuple->value.push_back(new OSSIA::Float(f.x));
        tuple->value.push_back(new OSSIA::Float(f.y));
        return tuple;
    }
};

/*
 * Class inheriting from ofParameter
 * Listeners (listening to i-score and GUI) can be added
 * By passing a std::type in argument, the OSSIA type is deduced in the class
 * */

template <class DataValue>
class Parameter : public ofParameter<DataValue>{
private:
    std::shared_ptr<Node> _parentNode = NULL;
    std::shared_ptr<Address> _address = NULL;

    /*
     * methods to communicate via OSSIA to i-score
     * */
    // Creates the node
    void createNode(string name,DataValue data){
        //creates node
        std::shared_ptr<Node> node = *(_parentNode->emplace(_parentNode->children().cend(), name));

        //set value
        auto val = MatchingType<DataValue>::convert(data);
        _address = node->createAddress(MatchingType<DataValue>::val);
        //_address->pushValue(val);
    }

    // Publishes value to the node
    void publishValue(DataValue other){
        auto val = MatchingType<DataValue>::convert(other);
        _address->pushValue(val);
    }

    // Pulls the node value
    DataValue pullNodeValue(){
        //std::cout << ""<< std::endl;
        auto add = this->getAddress();
        std::cout << "plop"<< std::endl;

        // add->pullValue();
        OSSIA::Value * val = add->getValue()->clone();
        std::cout << "pipi"<< std::endl;
       val->getType();
       std::cout << "pipi2"<< std::endl;

        if(val->getType() == Value::Type::BOOL){
            Bool * tmp = (Bool*) val;
            std::cout << tmp->value<< std::endl;

        }
        else if(val->getType() == Value::Type::TUPLE){
            std::cout << "merde"<< std::endl;

        }
        else{
            std::cout << "gros caca"<< std::endl;

        }
        DataValue v = MatchingType<DataValue>::convertFromOssia(val);
        std::cout << "caca"<< std::endl;

        return v;
    }

public:
    Parameter() : ofParameter<DataValue>(){    }

    ~Parameter(){
        this->removeListener(this,&Parameter<DataValue>::listen);
    }

    // creates node and sets the name, the data
    Parameter & setup(std::shared_ptr<Node> parentNode, string name, DataValue data){
        _parentNode = parentNode;
        createNode(name,data);
        publishValue(data);
        this->set(name,data);
        return *this;
    }

    // creates node and sets the name, the data, the minimum and maximum value (for the gui)
    Parameter & setup(std::shared_ptr<Node> parentNode, string name,DataValue data,DataValue min,DataValue max){
        _parentNode = parentNode;
        createNode(name,data);
        publishValue(data);
        this->set(name,data,min,max);
        return *this;
    }

    // set without creating node (suppose that a node was created previously)
    Parameter & setupNoPublish(std::shared_ptr<Node> parentNode, string name,DataValue data,DataValue min,DataValue max){
        _parentNode = parentNode;
        this->set(name,data,min,max);
    }

    // Get the address of the node
    std::shared_ptr<Address> getAddress() const{
        if(_address != NULL){
            return _address;
        }

        for(const auto & child : _parentNode->children()){
            if (child->getName().compare(this->getName()) == 0){
                // _address =  child->getAddress();
                return child->getAddress();//add->getValue()
            }
        }
        return NULL;
    }

    // Listener for the GUI (but called also when i-score sends value)
    void listen(DataValue &data){
        // check if the value to be published is not already published
        std::cout << "listen data "<< data<<std::endl;

        std::cout << "listen pull "<< pullNodeValue()<<std::endl;

        if(pullNodeValue() != data){// i-score->GUI OK
            // std::cout << "listen puis publication"<<std::endl;

            //if(_publishedValue != data){
            publishValue(data);
        }
    }


    // Updates value of the parameter and publish to the node
    void update(DataValue data){
        publishValue(data);
        // change attribute value
        this->set(data);
    }
};

#endif // PARAMETER_H
