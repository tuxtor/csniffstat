/* 
 * File:   PacketAnalyser.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 11:36 PM
 */

#ifndef PACKETANALYSER_H
#define	PACKETANALYSER_H
#include "NetPcap.h"
#include <tbb/task.h>

class PacketAnalyser: public tbb::task {
public:
    PacketAnalyser();
    PacketAnalyser(tbb::concurrent_vector<pcappacket>* packetVector, int start, int lenght);
    PacketAnalyser(const PacketAnalyser& orig);
    virtual ~PacketAnalyser();
    
private:
    tbb::task* execute();
    void computeDirectly();
    tbb::concurrent_vector<pcappacket>* packetVector;
    void processPackage(pcappacket &entirePacket);
    int start;
    int lenght;
};

#endif	/* PACKETANALYSER_H */

