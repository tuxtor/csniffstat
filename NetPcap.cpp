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

void NetPcap::openNetworkDevice() {
    int snaplen = 64 * 1024; // Captures whitouth truncating in promiscous mode
    if ((pcap = pcap_open_live(device->name, snaplen, 1, 20, errbuf)) == NULL) {
        fprintf(stderr, "\nError opening adapter\n");
        return;
    }
    //Creating filters
    string expressionF = buildExpression();
    char expresion[expressionF.size()];
    strcpy(expresion, expressionF.c_str());
    /* Compile and apply the filter */
    cout<<"Expresion: "<<expresion<<endl;
    if (pcap_compile(pcap, &filter, expresion, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", expresion, pcap_geterr(pcap));
        return;
    }
    if (pcap_setfilter(pcap, &filter) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", expresion, pcap_geterr(pcap));
        return;
    }
}

void NetPcap::run() {

}

void NetPcap::close() {
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
