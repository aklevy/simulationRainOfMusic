#include "network.hpp"

using namespace OSSIA;
using namespace std;

Network::Network(){
    // declare this program "B" as Local device
    localProtocol = Local::create();
    localDevice = Device::create(localProtocol, "newDevice");

    // add a node "scene"
    localSceneNode = *(localDevice->emplace(localDevice->children().cend(), "scene"));

    // execution of publication on the networkThread thread
    std::thread t(&Network::publication, this);
    std::swap(t, networkThread);
}

Network::~Network(){
    networkThread.join();
}

void Network::publication(){
    auto minuitProtocol = Minuit::create("127.0.0.1", 13579, 9998);
    auto minuitDevice = Device::create(minuitProtocol, "i-score");

    while (true)
        ;
}

std::shared_ptr<Node> Network::getSceneNode(){
    return localSceneNode;
}

