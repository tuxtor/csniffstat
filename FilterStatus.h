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

