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

