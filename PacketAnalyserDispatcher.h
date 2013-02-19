/* 
 * File:   PacketAnalyserDispatcher.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 11:36 PM
 */

#ifndef PACKETANALYSERDISPATCHER_H
#define	PACKETANALYSERDISPATCHER_H
#include "NetPcap.h"

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
private:
    boost::thread dispatcherThread;
    PacketsBuffer *packetsBuffer;
};

#endif	/* PACKETANALYSERDISPATCHER_H */

