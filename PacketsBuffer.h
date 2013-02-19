/* 
 * File:   PacketsBuffer.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 11:11 AM
 */

#ifndef PACKETSBUFFER_H
#define	PACKETSBUFFER_H

#include<tbb/concurrent_queue.h>
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
    tbb::concurrent_queue<pcappacket> getPacketsAnalisysSublist(int start, int end);
    tbb::concurrent_queue<pcappacket> getAnalisysList();
    void cleanHeadElements(int size);
    int getSize();
private:
    //TODO volver estatico
    tbb::concurrent_queue<pcappacket> packetsList;
    int packetCount;
};

#endif	/* PACKETSBUFFER_H */

