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
    /*boost::posix_time::seconds workTime(5);
    cout << "Worker: running" << endl;
    boost::this_thread::sleep(workTime);*/
    while (true) {
        try{
            runAnalysis();
            boost::posix_time::seconds workTime(2);
            boost::this_thread::sleep(workTime);
        }catch(boost::thread_interrupted const&){
            break;
        }
    }

}

void PacketAnalyserDispatcher::runAnalysis() {
    tbb::concurrent_vector<pcappacket> analysisVector = packetsBuffer->getAnalisysVector();
    int copiedSize = analysisVector.size();
    //cout << "Vector size " << analysisVector.size() << endl;
    //cout << "Before cleaning" << packetsBuffer->getSize() << endl;
    //boost::posix_time::seconds workTime(1);
    //boost::this_thread::sleep(workTime);

    PacketAnalyser& a = *new(tbb::task::allocate_root()) PacketAnalyser(&analysisVector, 0, analysisVector.size());
    tbb::task::spawn_root_and_wait(a);

    packetsBuffer->cleanHeadElements(copiedSize);
    //cout << "After cleaning" << packetsBuffer->getSize() << endl;
}

void PacketAnalyserDispatcher::join() {
    dispatcherThread.join();
    dispatcherThread.detach();
    cout << "Detached thread\n";
}

void PacketAnalyserDispatcher::interrupt() {
    dispatcherThread.interrupt();
}

void PacketAnalyserDispatcher::close() {
    interrupt();
    join();
}