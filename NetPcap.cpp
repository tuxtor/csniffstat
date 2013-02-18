/* 
 * File:   NetPcap.cpp
 * Author: tuxtor
 * 
 * Created on February 17, 2013, 4:22 PM
 */


#include <iostream>

#include "NetPcap.h"
#include "FilterStatus.h"
#include "XMLProperties.h"
#include <boost/lexical_cast.hpp>
using namespace std;

NetPcap::NetPcap() {
    //this->packagesCount=0;
}

NetPcap::NetPcap(const NetPcap& orig) {
}

NetPcap::~NetPcap() {
}

void NetPcap::chooseNetworkDevice(int &inicId) {
    char *dev;
    pcap_if_t *alldevs;

    pcap_findalldevs(&alldevs, errbuf);
    int i = 0;

    for (device = alldevs; device; device = device->next) {
        printf("%d. %s", i++, device->name);
        if (device->description)
            printf(" (%s)\n", device->description);
        else
            printf(" (No description available)\n");
    }
    if (i > 0) {
        printf("Select nic > ");
        cin >> inicId;
        if (inicId > i || inicId<-2) {
            printf("Wrong nic number\n");
            inicId = -1;
        }
        /* Jump to the selected adapter */
        for (device = alldevs, i = 0; i < inicId; device = device->next, i++);
        printf("Selected %s device\n", device->name);
    } else {
        printf("No NICs available\n");
        inicId = -2;
    }
}

//Work with numbers

void NetPcap::setNetworkDevice(int &inicId) {
    char *dev;
    pcap_if_t *alldevs;

    pcap_findalldevs(&alldevs, errbuf);
    int i = 0;
    for (device = alldevs; device; device = device->next) {
        printf("%d. %s", i++, device->name);
        if (device->description)
            printf(" (%s)\n", device->description);
        else
            printf(" (No description available)\n");
    }
    /* Jump to the selected adapter */
    if (i > 0) {
        for (device = alldevs, i = 0; i < inicId; device = device->next, i++);
        printf("Selected %d - %s device\n", i, device->name);
    } else {
        printf("No NICs available\n");
        inicId = -2;
    }
}

//Work with chars

void NetPcap::setNetworkDevice(int &inicId, char* snicName) {
    char *dev;
    pcap_if_t *alldevs;

    pcap_findalldevs(&alldevs, errbuf);
    int i = 0;
    for (device = alldevs; device; device = device->next) {
        printf("%d. %s \n", i++, device->name);
        if (strcmp(device->name, snicName) == 0) {
            break;
        }
    }

    if (i > 0) {
        printf("Selected %d - %s device\n", i, device->name);
    } else {
        printf("No NICs available\n");
        inicId = -2;
    }
}

void NetPcap::openNetworkDevice() {
    if ((pcap = pcap_open_live(device->name, SNAP_LEN, 1, 20, errbuf)) == NULL) {
        fprintf(stderr, "\nError opening adapter\n");
        return;
    }
    //Creating filters
    string expressionF = buildExpression();
    char expresion[expressionF.size()];
    strcpy(expresion, expressionF.c_str());
    /* Compile and apply the filter */
    cout << "Expresion: " << expresion << endl;
    if (pcap_compile(pcap, &filter, expresion, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", expresion, pcap_geterr(pcap));
        return;
    }
    if (pcap_setfilter(pcap, &filter) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", expresion, pcap_geterr(pcap));
        return;
    }
}
int packagesCount;

void count_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    pcappacket cappacket = {packet, header};
    buffer.addPacket(cappacket);
    packagesCount++;
    printf("\nPacket number %d:\n", packagesCount);
}

void NetPcap::run() {
    //pcap_loop(pcap, -1, NetPcap::count_packet, NULL);
    cout<<"Capturing packages\n";
    pcap_loop(pcap, -1, count_packet, NULL);

}

void NetPcap::close() {
    pcap_breakloop(pcap);
    pcap_close(pcap);
}

string NetPcap::buildExpression() {
    string filter = "";
    list<string> separatedFilters;
    FilterStatus fs;
    if (fs.isTCPActivated()) {
        separatedFilters.push_back("tcp");
    }
    if (fs.isUDPActivated()) {
        separatedFilters.push_back("udp");
    }
    if (fs.isICMPActivated()) {
        separatedFilters.push_back("icmp");
    }
    if (fs.isTCPACKActivated()) {
        separatedFilters.push_back("(tcp[tcpflags] & (tcp-ack) != 0)");
    }
    if (fs.isTCPFINActivated()) {
        separatedFilters.push_back("(tcp[tcpflags] & (tcp-fin) != 0)");
    }
    if (fs.isTCPSYNActivated()) {
        separatedFilters.push_back("(tcp[tcpflags] & (tcp-syn) != 0)");
    }

    for (int i = 0; i < separatedFilters.size(); i++) {
        filter += separatedFilters.front();
        if ((i + 1) != separatedFilters.size()) {
            filter += " or ";
        }
        separatedFilters.pop_front();
    }
    //filter = "port " + xmlProps.GetPortToFilter() + " and (" + filter + ")";

    if (xmlProps.GetPortToFilter() != -1) {
        string portFilter = "port " + boost::lexical_cast<std::string > (xmlProps.GetPortToFilter());
        filter = portFilter + " and (" + filter + ")";
    }
    return filter;
}

void NetPcap::got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    static int count = 1; /* packet counter */

    /* declare pointers to packet headers */
    const struct sniff_ethernet *ethernet; /* The ethernet header [1] */
    const struct sniff_ip *ip; /* The IP header */
    const struct sniff_tcp *tcp; /* The TCP header */
    const char *payload; /* Packet payload */

    int size_ip;
    int size_tcp;
    int size_payload;

    printf("\nPacket number %d:\n", count);
    count++;

    /* define ethernet header */
    ethernet = (struct sniff_ethernet*) (packet);

    /* define/compute ip header offset */
    ip = (struct sniff_ip*) (packet + SIZE_ETHERNET);
    size_ip = IP_HL(ip)*4;
    if (size_ip < 20) {
        printf("   * Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

    /* print source and destination IP addresses */
    printf("       From: %s\n", inet_ntoa(ip->ip_src));
    printf("         To: %s\n", inet_ntoa(ip->ip_dst));

    /* determine protocol */
    switch (ip->ip_p) {
        case IPPROTO_TCP:
            printf("   Protocol: TCP\n");
            break;
        case IPPROTO_UDP:
            printf("   Protocol: UDP\n");
            return;
        case IPPROTO_ICMP:
            printf("   Protocol: ICMP\n");
            return;
        case IPPROTO_IP:
            printf("   Protocol: IP\n");
            return;
        default:
            printf("   Protocol: unknown\n");
            return;
    }

    /*
     *  OK, this packet is TCP.
     */

    /* define/compute tcp header offset */
    tcp = (struct sniff_tcp*) (packet + SIZE_ETHERNET + size_ip);
    size_tcp = TH_OFF(tcp)*4;
    if (size_tcp < 20) {
        printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }

    printf("   Src port: %d\n", ntohs(tcp->th_sport));
    printf("   Dst port: %d\n", ntohs(tcp->th_dport));

//    /* define/compute tcp payload (segment) offset */
//    payload = (u_char *) (packet + SIZE_ETHERNET + size_ip + size_tcp);
//
//    /* compute tcp payload (segment) size */
//    size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);
//
//    /*
//     * Print payload data; it might be binary, so don't just
//     * treat it as a string.
//     */
//    if (size_payload > 0) {
//        printf("   Payload (%d bytes):\n", size_payload);
//        print_payload(payload, size_payload);
//    }

    return;
};

void NetPcap::print_hex_ascii_line(const u_char *payload, int len, int offset) {
    int i;
    int gap;
    const u_char *ch;

    /* offset */
    printf("%05d   ", offset);

    /* hex */
    ch = payload;
    for (i = 0; i < len; i++) {
        printf("%02x ", *ch);
        ch++;
        /* print extra space after 8th byte for visual aid */
        if (i == 7)
            printf(" ");
    }
    /* print space to handle line less than 8 bytes */
    if (len < 8)
        printf(" ");

    /* fill hex gap with spaces if not full line */
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            printf("   ");
        }
    }
    printf("   ");

    /* ascii (if printable) */
    ch = payload;
    for (i = 0; i < len; i++) {
        if (isprint(*ch))
            printf("%c", *ch);
        else
            printf(".");
        ch++;
    }

    printf("\n");

    return;
};

void NetPcap::print_payload(const u_char *payload, int len) {
    int len_rem = len;
    int line_width = 16; /* number of bytes per line */
    int line_len;
    int offset = 0; /* zero-based offset counter */
    const u_char *ch = payload;

    if (len <= 0)
        return;

    /* data fits on one line */
    if (len <= line_width) {
        print_hex_ascii_line(ch, len, offset);
        return;
    }

    /* data spans multiple lines */
    for (;;) {
        /* compute current line length */
        line_len = line_width % len_rem;
        /* print line */
        print_hex_ascii_line(ch, line_len, offset);
        /* compute total remaining */
        len_rem = len_rem - line_len;
        /* shift pointer to remaining bytes to print */
        ch = ch + line_len;
        /* add offset */
        offset = offset + line_width;
        /* check if we have line width chars or less */
        if (len_rem <= line_width) {
            /* print last line and get out */
            print_hex_ascii_line(ch, len_rem, offset);
            break;
        }
    }

    return;
};

