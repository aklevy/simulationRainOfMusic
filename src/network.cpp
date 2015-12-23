#include "network.hpp"


using namespace OSSIA;
using namespace std;

network::network(){
    std::thread t(&network::publication, this);
    std::swap(t, networkThread);
}

network::~network(){
    networkThread.join();
}

void network::publication(){
    // declare this program "B" as Local device
    auto localProtocol = Local::create();
    auto localDevice = Device::create(localProtocol, "B");

    // add a node "scene"
    auto localSceneNode = *(localDevice->emplace(localDevice->children().cend(), "scene"));

    // add two floats (test)
    auto localFloatNode = *(localSceneNode->emplace(localSceneNode->children().cend(), "my_float"));
    auto localFloatAddress = localFloatNode->createAddress(Value::Type::FLOAT);

    auto localFloatbisNode = *(localSceneNode->emplace(localSceneNode->children().cend(), "my_float_bis"));
    auto localFloatbisAddress = localFloatbisNode->createAddress(Value::Type::FLOAT);

    /*
    Float f(0.5);
    localFloatAddress->pushValue(&f);
    Float fbis(-0.5);
    localFloatbisAddress->pushValue(&fbis);
    */

    auto minuitProtocol = Minuit::create("127.0.0.1", 9999, 6666);
    auto minuitDevice = Device::create(minuitProtocol, "i-score");

    while (true)
        ;
}
