/* 
 * File:   PacketAnalyserDispatcher.cpp
 * Author: tuxtor
 * 
 * Created on February 18, 2013, 11:36 PM
 */

#include "PacketAnalyserDispatcher.h"
using namespace std;
PacketAnalyserDispatcher::PacketAnalyserDispatcher() {
}

PacketAnalyserDispatcher::PacketAnalyserDispatcher(PacketsBuffer *buffer) {
    this->packetsBuffer = buffer;
}

PacketAnalyserDispatcher::PacketAnalyserDispatcher(const PacketAnalyserDispatcher& orig) {
}

PacketAnalyserDispatcher::~PacketAnalyserDispatcher() {
}

void PacketAnalyserDispatcher::start() {
    dispatcherThread = boost::thread(&PacketAnalyserDispatcher::run, this);
}

void PacketAnalyserDispatcher::run() {
    boost::posix_time::seconds workTime(5);
    cout << "Worker: running" << endl;
    boost::this_thread::sleep(workTime);
    runAnalysis();
    cout << "Worker: finished" << endl;

}
void PacketAnalyserDispatcher::runAnalysis() {
    //copy from buffer
    tbb::concurrent_queue<pcappacket> analysisList = packetsBuffer->getAnalisysList();
    int copiedSize = analysisList.unsafe_size();
    cout << "I copied " << copiedSize << endl;
    //Do analysis
    //pop from buffer
    /*cout << "Before cleaning" << packetsBuffer->getSize() << endl;
    boost::posix_time::seconds workTime(1);
    boost::this_thread::sleep(workTime);*/
    packetsBuffer->cleanHeadElements(copiedSize);
    //cout << "After cleaning" << packetsBuffer->getSize() << endl;
}
void PacketAnalyserDispatcher::join() {
    dispatcherThread.join();
    dispatcherThread.detach();
    cout<<"Detached thread\n";
}

void PacketAnalyserDispatcher::interrupt() {
    dispatcherThread.interrupt();
}

void PacketAnalyserDispatcher::close() {
    interrupt();
    join();
}