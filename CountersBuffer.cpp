/* 
 * File:   CountersBuffer.cpp
 * Author: tuxtor
 * 
 * Created on February 19, 2013, 3:11 PM
 */

#include <tbb/spin_mutex.h>
#include <stdio.h>
#include <sstream>

#include "CountersBuffer.h"

using namespace std;
CountersBuffer::CountersBuffer() {
}

CountersBuffer::CountersBuffer(const CountersBuffer& orig) {
}

CountersBuffer::~CountersBuffer() {
}

void CountersBuffer::AddAll(int tcpAcc, int udpAcc, int icmpAcc, int tcpAckAcc, int tcpFinAcc, int tcpSynAcc, int totalAcc) {
    lock.acquire(CountersMutex);
    this->tcpAcc += tcpAcc;
    this->udpAcc += udpAcc;
    this->icmpAcc += icmpAcc;
    this->tcpAckAcc += tcpAckAcc;
    this->tcpFinAcc += tcpFinAcc;
    this->tcpSynAcc += tcpSynAcc;
    this->totalAcc += totalAcc;
    this->grandTotal += totalAcc;
    lock.release();
}

void CountersBuffer::AddTotalAcc() {
    lock.acquire(CountersMutex);
    this->totalAcc++;
    lock.release();
}

void CountersBuffer::AddTcpSynAcc() {
    lock.acquire(CountersMutex);
    this->tcpSynAcc++;
    lock.release();
}

void CountersBuffer::AddTcpFinAcc() {
    lock.acquire(CountersMutex);
    this->tcpFinAcc++;
    lock.release();
}

void CountersBuffer::AddTcpAckAcc() {
    lock.acquire(CountersMutex);
    this->tcpAckAcc++;
    lock.release();
}

void CountersBuffer::AddIcmpAcc() {
    lock.acquire(CountersMutex);
    this->icmpAcc++;
    lock.release();
}

void CountersBuffer::AddUdpAcc() {
    lock.acquire(CountersMutex);
    this->udpAcc++;
    lock.release();
}

void CountersBuffer::AddTcpAcc() {
    lock.acquire(CountersMutex);
    this->tcpAcc++;
    lock.release();
}

void CountersBuffer::ZeroCounters() {
    lock.acquire(CountersMutex);
    this->tcpAcc = 0;
    this->udpAcc = 0;
    this->icmpAcc = 0;
    this->tcpAckAcc = 0;
    this->tcpFinAcc = 0;
    this->tcpSynAcc = 0;
    this->totalAcc = 0;
    lock.release();
}

void CountersBuffer::PrintValues(){
    cout<<tcpAcc<<"|"<<udpAcc<<"|"<<icmpAcc<<"|"<<tcpAckAcc<<"|"<<tcpFinAcc<<"|"<<tcpSynAcc<<"|"<<totalAcc<<std::endl;
}

void CountersBuffer::PrintAndRestartGrandTotal(){
    cout<<"Grand Total "<<grandTotal<<endl;
    grandTotal=0;
}