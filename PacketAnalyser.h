/* 
 * File:   PacketAnalyser.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 11:36 PM
 */

#ifndef PACKETANALYSER_H
#define	PACKETANALYSER_H
#include "NetPcap.h"
#include "CountersBuffer.h"
#include <tbb/task.h>
#include <tbb/task_scheduler_init.h>
#include <iostream>
class PacketAnalyser: public tbb::task {
public:
    PacketAnalyser();
    PacketAnalyser(tbb::concurrent_vector<pcappacket>* packetVector, CountersBuffer* countersBuffer, int start, int lenght);
    PacketAnalyser(const PacketAnalyser& orig);
    virtual ~PacketAnalyser();
    
private:
    tbb::task* execute();
    void computeDirectly();
    tbb::concurrent_vector<pcappacket>* packetVector;
    //void processPackage(pcappacket &entirePacket, int &tcpAcc,int &udpAcc,int &icmpAcc,int &tcpAckAcc,int &tcpFinAcc,int &tcpSynAcc,int &totalAcc);
    void processPackage(pcappacket &entirePacket);
    int start;
    int lenght;
    CountersBuffer* countersBuffer;
};

#endif	/* PACKETANALYSER_H */

