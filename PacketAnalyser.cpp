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

#include "PacketAnalyser.h"

PacketAnalyser::PacketAnalyser() {
}

PacketAnalyser::PacketAnalyser(tbb::concurrent_vector<pcappacket>* packetVector, CountersBuffer* countersBuffer, int start, int lenght) {
    this->packetVector = packetVector;
    this->countersBuffer = countersBuffer;
    this->start = start;
    //printf("Constructing analyzer %d\n",lenght);
    this->lenght = lenght;
}

PacketAnalyser::PacketAnalyser(const PacketAnalyser& orig) {
}

PacketAnalyser::~PacketAnalyser() {
}

tbb::task* PacketAnalyser::execute() {
    int mainThreads = 2;
    int threshold = 10000;

    if (lenght < threshold) {
        //printf("Computing directly");
        computeDirectly();
    } else {
        int split = lenght / mainThreads;
        tbb::task_list list;
        this->set_ref_count(3);
        //printf("Spliting Length %d\n", lenght);
        PacketAnalyser& a = *new( allocate_child()) PacketAnalyser(packetVector, countersBuffer, start, split);
        int seconSplit;
        if((lenght%2)==0){
            seconSplit = split;
        }else{
            seconSplit = split+1;
        }
        PacketAnalyser& b = *new( allocate_child()) PacketAnalyser(packetVector, countersBuffer, start + split, seconSplit);
        list.push_back(a);
        list.push_back(b);
        // Start a running and wait for all children (a and b).
        spawn_and_wait_for_all(list);
    }
    return NULL;
}

//void PacketAnalyser::computeDirectly() {
//    int packNu=0;
//    int tcpAcc, udpAcc, icmpAcc, tcpAckAcc, tcpFinAcc, tcpSynAcc, totalAcc;
//    for (int i = start; (i < start + lenght) && (i<packetVector->size()); i++) {
//        //processPackage(packetVector->at(i));
//        packNu++;
//        //processPackage(packetVector->at(i), tcpAcc, udpAcc, icmpAcc, tcpAcc, tcpFinAcc, tcpSynAcc, totalAcc);
//    }
//    printf("Computed %d - packnu %d - processed %d \n",lenght, packNu, totalAcc);
//}

void PacketAnalyser::computeDirectly() {
    int packNu = 0;
    int tcpAcc = 0, udpAcc = 0, icmpAcc = 0, tcpAckAcc = 0, tcpFinAcc = 0, tcpSynAcc = 0, totalAcc = 0;
    for (int i = start; (i < start + lenght) && (i < packetVector->size()); i++) {
        pcappacket entirePacket = packetVector->at(i);
        packNu++;
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

        totalAcc++;
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
        //processPackage(packetVector->at(i), tcpAcc, udpAcc, icmpAcc, tcpAcc, tcpFinAcc, tcpSynAcc, totalAcc);
    }
    countersBuffer->AddAll(tcpAcc,udpAcc,icmpAcc,tcpAckAcc,tcpFinAcc,tcpSynAcc,totalAcc);
    //printf("Computed %d - packnu %d - processed %d \n", lenght, packNu, totalAcc);
}


//void PacketAnalyser::processPackage(pcappacket &entirePacket, int &tcpAcc,int &udpAcc,int &icmpAcc,int &tcpAckAcc,int &tcpFinAcc,int &tcpSynAcc,int & totalAcc) {

void PacketAnalyser::processPackage(pcappacket &entirePacket) {
    int tcpAcc, udpAcc, icmpAcc, tcpAckAcc, tcpFinAcc, tcpSynAcc, totalAcc;
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

    totalAcc++;
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

    //printf("tcpAcc: %d, udpAcc: %d, icmpAcc: %d \n",tcpAcc, udpAcc, icmpAcc);
    //countersBuffer->AddAll(tcpAcc,udpAcc,icmpAcc,tcpAckAcc,tcpFinAcc,tcpSynAcc,totalAcc);
}
