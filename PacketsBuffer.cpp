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
    cout << "Size " << packetsList.size() << endl;
};

tbb::concurrent_queue<pcappacket> PacketsBuffer::getPacketsAnalisysSublist(int start, int end){
    
};

tbb::concurrent_queue<pcappacket> * PacketsBuffer::getAnalisysList(int start, int end){
    
};