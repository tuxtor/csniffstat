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
    //cout << packetCount++ << endl;
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

tbb::concurrent_queue<pcappacket> PacketsBuffer::getPacketsAnalisysSublist(int start, int end){
    
}


pcappacket*  PacketsBuffer::getAnalisysArray(){
    //copy
    int actualSize = packetsList.unsafe_size();
    pcappacket* packetArray = new pcappacket[actualSize];

    for (int i = 0; i < actualSize; i++) {
         packetsList.try_pop(packetArray[i]);
    }
    return packetArray;
}

tbb::concurrent_queue<pcappacket> PacketsBuffer::getAnalisysList(){
    //copy
    return tbb::concurrent_queue<pcappacket>(packetsList);
};

