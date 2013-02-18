/* 
 * File:   FilterStatus.h
 * Author: tuxtor
 *
 * Created on February 17, 2013, 8:09 PM
 */

#ifndef FILTERSTATUS_H
#define	FILTERSTATUS_H

class FilterStatus {
public:
    FilterStatus();
    FilterStatus(const FilterStatus& orig);
    virtual ~FilterStatus();

    bool isTCPActivated();
    bool isUDPActivated();
    bool isICMPActivated();
    bool isTCPSYNActivated();
    bool isTCPFINActivated();
    bool isTCPACKActivated();
    int getNumberOfActivatedFilters();
    //Manipulation functions
    void activateTCP();
    void activateUDP();
    void activateICMP();
    void activateTCPACK();
    void activateTCPFIN();
    void activateTCPSYN();

    void deactivateTCP();
    void deactivateUDP();
    void deactivateICMP();
    void deactivateTCPACK();
    void deactivateTCPFIN();
    void deactivateTCPSYN();
private:
    bool tcp;
    bool udp;
    bool icmp;
    bool tcpACK;
    bool tcpFIN;
    bool tcpSYN;
    int numberOfActiveFilters;
};

#endif	/* FILTERSTATUS_H */

