/* 
 * File:   PacketAnalyserDispatcher.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 11:36 PM
 */

#ifndef PACKETANALYSERDISPATCHER_H
#define	PACKETANALYSERDISPATCHER_H


#include "NetPcap.h"
#include "PacketAnalyser.h"
#include "CountersBuffer.h"

class PacketAnalyserDispatcher {
public:
    PacketAnalyserDispatcher();
    PacketAnalyserDispatcher(PacketsBuffer *buffer);
    PacketAnalyserDispatcher(const PacketAnalyserDispatcher& orig);
    virtual ~PacketAnalyserDispatcher();
    void start();
    void run();
    void runAnalysis();
    void join();
    void close();
    void interrupt();
    CountersBuffer countersBuffer;
private:
    boost::thread dispatcherThread;
    PacketsBuffer *packetsBuffer;
    //std::vector<pcappacket> toSimpleVector(tbb::concurrent_queue<pcappacket> &queue);
};

#endif	/* PACKETANALYSERDISPATCHER_H */

