/* 
 * File:   NetPcap.h
 * Author: tuxtor
 *
 * Created on February 17, 2013, 4:22 PM
 */

#ifndef NETPCAP_H
#define	NETPCAP_H
#include <pcap.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <vector>

#include "XMLProperties.h"
class NetPcap {
public:
    NetPcap();
    NetPcap(const NetPcap& orig);
    virtual ~NetPcap();
    void chooseNetworkDevice(int &inicId);
    void setNetworkDevice(int &inicId);
    void openNetworkDevice();
    void run();
    void close();
    std::string buildExpression();
private:
    pcap_if_t *device;
    pcap_t *pcap;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program filter; /* The compiled filter */
    bpf_u_int32 net;
    //std::string buildExpression();
    XMLProperties xmlProps;
};

#endif	/* NETPCAP_H */

