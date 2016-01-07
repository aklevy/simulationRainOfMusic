#ifndef PARAMETER_H
#define PARAMETER_H

#include "ofMain.h"
#include "network.hpp"

template<typename> struct MatchingType;

template<> struct MatchingType<float> {
        using ofx_type = float;
        using ossia_type = OSSIA::Float;
        static constexpr const auto val = OSSIA::Value::Type::FLOAT;

        static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<double> {
    using ofx_type = double;
        static constexpr const auto val = OSSIA::Value::Type::FLOAT;
        using ossia_type = OSSIA::Float;

        static ossia_type* convert(ofx_type f) { return new ossia_type{float(f)}; }
};
template<> struct MatchingType<int> {
    using ofx_type = int;
        static constexpr const auto val = OSSIA::Value::Type::INT;
        using ossia_type = OSSIA::Int;

        static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<bool> {
    using ofx_type = bool;
        static constexpr const auto val = OSSIA::Value::Type::BOOL;
        using ossia_type = OSSIA::Bool;

        static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<string> {
    using ofx_type = std::string;
        static constexpr const auto val = OSSIA::Value::Type::STRING;
        using ossia_type = OSSIA::String;

        static ossia_type* convert(ofx_type f) { return new ossia_type{f}; }
};
template<> struct MatchingType<ofVec3f> {
    using ofx_type = ofVec3f;
        static constexpr const auto val = OSSIA::Value::Type::TUPLE;
        using ossia_type = OSSIA::Tuple;

        static ossia_type* convert(ofx_type f) {
            auto tuple = new ossia_type;
            tuple->value.reserve(3);
            tuple->value.push_back(new OSSIA::Float(f.x));
            tuple->value.push_back(new OSSIA::Float(f.y));
            tuple->value.push_back(new OSSIA::Float(f.z));
            return tuple;
        }
};

template <class DataValue>
class Parameter : public ofParameter<DataValue>{
private:
    std::shared_ptr<Node> _botNode;
    std::shared_ptr<Address> _address;
public:
    Parameter(){}

    Parameter(shared_ptr<Node> parentBotNode,
              DataValue data,
              string name):
        ofParameter<DataValue>(name,data),
        _botNode(parentBotNode){

        //creates node
        std::shared_ptr<Node> node = *(_botNode->emplace(_botNode->children().cend(), name));

        //set value
        auto val = MatchingType<DataValue>::convert(data);
        _address = node->createAddress(MatchingType<DataValue>::val);
        _address->pushValue(val);

        // adds listener to listen to the gui
       // this->addListener(this,&Parameter::listen);
    }

    // sets the name, the minimum and maximum value (for the gui)
    void setup(string name){
        this->setName(name);
    }
    void setup(string name,DataValue min,DataValue max){
        this->setName(name);
        this->setMin(min);
        this->setMax(max);
    }

    std::shared_ptr<Address> getAddress() const{
        return _address;
    }

    void listen(DataValue &data){
        this->update(data);
    }


    void update(DataValue other){

        auto val = MatchingType<DataValue>::convert(other);
        // change attribute value
        this->set(other);
        // update the changed attribute value
        _address->pushValue(val);
    }
};

#endif // PARAMETER_H
