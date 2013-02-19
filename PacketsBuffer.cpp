/* 
 * Copyright (C) 2013  Víctor Orozco
 * 
 * This file is part of csniffstat.
 * 
 * csniffstat program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * csniffstat program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    //cout << "Copying queue size " << queue.unsafe_size() << endl;
    pcappacket packet;
    int i=0;
    while (queue.try_pop(packet)) {
        returnVector.push_back(packet);
    }
    return returnVector;
};
