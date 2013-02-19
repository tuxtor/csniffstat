/* 
 * File:   CountersBuffer.h
 * Author: tuxtor
 *
 * Created on February 19, 2013, 3:11 PM
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

