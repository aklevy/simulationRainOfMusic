#include "network.hpp"

using namespace OSSIA;
using namespace std;

Network::Network(){
    _simRunning = true;

    // declare this program "B" as Local device
    _localProtocol = Local::create();
    _localDevice = Device::create(_localProtocol, "newDevice");

    // add a node "scene"
    _localSceneNode = *(_localDevice->emplace(_localDevice->children().cend(), "scene"));

    // execution of publication on the networkThread thread
    std::thread t(&Network::publication, this);
    std::swap(t, _networkThread);
}

Network::~Network(){
    _networkThread.join();
}

void Network::publication(){
    auto minuitProtocol = Minuit::create("127.0.0.1", 13579, 9998);
    auto minuitDevice = Device::create(minuitProtocol, "i-score");

    while (_simRunning)
        ;

    std::cout << "fini"<<std::endl;
}

std::shared_ptr<Node> Network::getSceneNode(){
    return _localSceneNode;
}

void Network::setSimRunning(bool b){
    _simRunning = b;
}
