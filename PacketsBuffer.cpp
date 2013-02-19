/* 
 * File:   PacketsBuffer.cpp
 * Author: tuxtor
 * 
 * Created on February 18, 2013, 11:11 AM
 */

#include "PacketsBuffer.h"
using namespace std;

PacketsBuffer::PacketsBuffer() {
}

PacketsBuffer::PacketsBuffer(const PacketsBuffer& orig) {
}

PacketsBuffer::~PacketsBuffer() {
}

void PacketsBuffer::addPacket(pcappacket packet){
    packetsList.push(packet);
    cout << packetCount++ << endl;
}

void PacketsBuffer::cleanHeadElements(int size){
    pcappacket temp;
    for (int i = 0; i < size; i++) {
        packetsList.try_pop(temp);
    }
}

int PacketsBuffer::getSize(){
    packetsList.unsafe_size();
};

tbb::concurrent_queue<pcappacket> PacketsBuffer::getAnalisysList(){
    //copy
    return tbb::concurrent_queue<pcappacket>(packetsList);
};

tbb::concurrent_vector<pcappacket> PacketsBuffer::getAnalisysVector(){
    //copy
    tbb::concurrent_queue<pcappacket> copyQueue(packetsList);
    return PacketsBuffer::toVector(copyQueue);
};

tbb::concurrent_vector<pcappacket> PacketsBuffer::toVector(tbb::concurrent_queue<pcappacket> &queue) {
    //copy
    tbb::concurrent_vector<pcappacket> returnVector;
    cout << "Copying queue size " << queue.unsafe_size() << endl;
    pcappacket packet;
    int i=0;
    while (queue.try_pop(packet)) {
        returnVector.push_back(packet);
    }
    return returnVector;
};
