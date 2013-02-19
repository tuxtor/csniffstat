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

#ifndef COUNTERSBUFFER_H
#define	COUNTERSBUFFER_H
#include <tbb/mutex.h>
#include <iostream>
class CountersBuffer {
public:
    CountersBuffer();
    CountersBuffer(const CountersBuffer& orig);
    virtual ~CountersBuffer();
    void AddTotalAcc();
    void AddTcpSynAcc();
    void AddTcpFinAcc();
    void AddTcpAckAcc();
    void AddIcmpAcc();
    void AddUdpAcc();
    void AddTcpAcc();
    void AddAll(int tcpAcc, int udpAcc, int icmpAcc, int tcpAckAcc, int tcpFinAcc, int tcpSynAcc, int totalAcc);
    void ZeroCounters();
    void PrintValues();
    void PrintAndRestartGrandTotal();
private:
    int tcpAcc, udpAcc, icmpAcc, tcpAckAcc, tcpFinAcc, tcpSynAcc, totalAcc;
    long int grandTotal;
    typedef tbb::spin_mutex CountersMutexType;
    CountersMutexType CountersMutex;
    CountersMutexType::scoped_lock lock;
};

#endif	/* COUNTERSBUFFER_H */

