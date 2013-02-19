/* 
 * File:   PacketAnalyser.cpp
 * Author: tuxtor
 * 
 * Created on February 18, 2013, 11:36 PM
 */

#include "PacketAnalyser.h"

PacketAnalyser::PacketAnalyser() {
}

PacketAnalyser::PacketAnalyser(tbb::concurrent_vector<pcappacket>* packetVector, int start, int lenght) {
    this->packetVector = packetVector;
    this->start = start;
    this->lenght = lenght;
}

PacketAnalyser::PacketAnalyser(const PacketAnalyser& orig) {
}

PacketAnalyser::~PacketAnalyser() {
}

tbb::task* PacketAnalyser::execute() {
    int mainThreads = 2;
    int threshold = 1000;

    if (lenght < threshold) {
        computeDirectly();
    } else {
        int split = lenght / mainThreads;
        tbb::task_list list;
        
        PacketAnalyser& a = *new( allocate_child()) PacketAnalyser(packetVector, start, split);
        PacketAnalyser& b = *new( allocate_child()) PacketAnalyser(packetVector, start+split, split);
        list.push_back(a);
        list.push_back(b);
        // Start a running and wait for all children (a and b).
        spawn_and_wait_for_all(list);
    }
    return NULL;
}

void PacketAnalyser::computeDirectly() {    
    for (int i = start; i < start + lenght; i++) {
        processPackage(packetVector->at(i));

    }
}

void PacketAnalyser::processPackage(pcappacket &entirePacket) {
    int tcpAcc = 0, udpAcc = 0, icmpAcc = 0, tcpAckAcc = 0, tcpFinAcc = 0, tcpSynAcc = 0, totalAcc = 0;
    const struct pcap_pkthdr *header = entirePacket.header;
    const u_char *packet = entirePacket.packet;
    /* declare pointers to packet headers */
    const struct sniff_ethernet *ethernet; /* The ethernet header [1] */
    const struct sniff_ip *ip; /* The IP header */
    const struct sniff_tcp *tcp; /* The TCP header */
    const char *payload; /* Packet payload */

    int size_ip;
    int size_tcp;
    int size_payload;

    //printf("\nPacket number %d:\n", count);
    ethernet = (struct sniff_ethernet*) (packet);

    /* define/compute ip header offset */
    ip = (struct sniff_ip*) (packet + SIZE_ETHERNET);
    size_ip = IP_HL(ip)*4;
    if (size_ip < 20) {
        printf("   * Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

    /* determine protocol */
    switch (ip->ip_p) {
        case IPPROTO_TCP:
            tcpAcc++;
            //Procesar subtipo
            break;
        case IPPROTO_UDP:
            //printf("   Protocol: UDP\n");
            udpAcc++;
            break;
        case IPPROTO_ICMP:
            icmpAcc++;
            //printf("   Protocol: ICMP\n");
            break;
        default:
            //printf("   Protocol: unknown\n");
            break;
    }
    
    /* print source and destination IP addresses */
    
    printf("tcpAcc: %d, udpAcc: %d, icmpAcc: %d \n",tcpAcc, udpAcc, icmpAcc);

}
