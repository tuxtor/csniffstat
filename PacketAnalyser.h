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

