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
    //cout << "Vector size " << copiedSize << endl;
    //cout << "Before cleaning" << packetsBuffer->getSize() << endl;
    //boost::posix_time::seconds workTime(1);
    //boost::this_thread::sleep(workTime);
    //tbb::task_scheduler_init init(8);
    PacketAnalyser& a = *new(tbb::task::allocate_root()) PacketAnalyser(&analysisVector, &countersBuffer, 0, copiedSize);
    tbb::task::spawn_root_and_wait(a);

    packetsBuffer->cleanHeadElements(copiedSize);
    //cout << "After cleaning" << packetsBuffer->getSize() << endl;
    //countersBuffer.PrintValues();
    //persist data
    countersBuffer.ZeroCounters();
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