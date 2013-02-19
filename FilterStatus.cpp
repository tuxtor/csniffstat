/* 
 * File:   FilterStatus.cpp
 * Author: tuxtor
 * 
 * Created on February 17, 2013, 8:09 PM
 */

#include "FilterStatus.h"

FilterStatus::FilterStatus() {
    tcp = true;
    //TODO restore this filter
    udp = true;
    icmp = true;
    tcpSYN = true;
    tcpFIN = true;
    tcpACK = true;
    numberOfActiveFilters = 0;
}

FilterStatus::FilterStatus(const FilterStatus& orig) {
}

FilterStatus::~FilterStatus() {
}

int FilterStatus::getNumberOfActivatedFilters() {
    return numberOfActiveFilters;
}

bool FilterStatus::isTCPActivated() {
    return tcp;
}

bool FilterStatus::isUDPActivated() {
    return udp;
}

bool FilterStatus::isICMPActivated() {
    return icmp;
}

bool FilterStatus::isTCPSYNActivated() {
    return tcpSYN;
}

bool FilterStatus::isTCPFINActivated() {
    return tcpFIN;
}

bool FilterStatus::isTCPACKActivated() {
    return tcpACK;
}

/* Flag manipulation functions*/

void FilterStatus::activateTCP() {
    if (!tcp) {
        tcp = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateTCP() {
    if (tcp) {
        tcp = false;
        numberOfActiveFilters--;
    }
}

void FilterStatus::activateUDP() {
    if (!udp) {
        udp = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateUDP() {
    if (udp) {
        udp = false;
        numberOfActiveFilters--;
    }
}

void FilterStatus::activateICMP() {
    if (!icmp) {
        icmp = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateICMP() {
    if (icmp) {
        icmp = false;
        numberOfActiveFilters--;
    }
}

void FilterStatus::activateTCPSYN() {
    if (!tcpSYN) {
        tcpSYN = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateTCPSYN() {
    if (tcpSYN) {
        tcpSYN = false;
        numberOfActiveFilters--;
    }
}

void FilterStatus::activateTCPFIN() {
    if (!tcpFIN) {
        tcpFIN = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateTCPFIN() {
    if (tcpFIN) {
        tcpFIN = false;
        numberOfActiveFilters--;
    }
}

void FilterStatus::activateTCPACK() {
    if (!tcpACK) {
        tcpACK = true;
        numberOfActiveFilters++;
    }
}

void FilterStatus::deactivateTCPACK() {
    if (tcpACK) {
        tcpACK = false;
        numberOfActiveFilters--;
    }
}
