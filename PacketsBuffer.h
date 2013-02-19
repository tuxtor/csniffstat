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

#ifndef PACKETSBUFFER_H
#define	PACKETSBUFFER_H

#include<tbb/concurrent_queue.h>
#include<tbb/concurrent_vector.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
struct pcappacket {
    const u_char *packet;
    const struct pcap_pkthdr *header;
};

class PacketsBuffer {
public:
    PacketsBuffer();
    PacketsBuffer(const PacketsBuffer& orig);
    virtual ~PacketsBuffer();
    void addPacket(pcappacket packet);
    
    tbb::concurrent_vector<pcappacket> getAnalisysVector();
    void cleanHeadElements(int size);
    int getSize();
private:
    //TODO volver estatico
    tbb::concurrent_queue<pcappacket> packetsList;
    int packetCount;
    tbb::concurrent_queue<pcappacket> getAnalisysList();
    tbb::concurrent_vector<pcappacket> toVector(tbb::concurrent_queue<pcappacket> &queue);
};

#endif	/* PACKETSBUFFER_H */

