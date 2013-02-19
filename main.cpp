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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
//---
#include "NetPcap.h"
#include "PacketAnalyserDispatcher.h"
using namespace std;

//XML Scanner
//DataManager
//ThreadDispatcher
int istatus;
int inicId = -1;

void runCapture();
void shutdown();
void restartAll();
void setNic();

PacketsBuffer packetsBuffer;
NetPcap netPcap(&packetsBuffer);
PacketAnalyserDispatcher dispatcher(&packetsBuffer);

int main(int nArg, char* pszArgs[]) {
    //Initializing objects
    //Parsing XML properties
    //si no hay argumentos preguntar por una nic
    if (nArg <= 1) {
        printf("Asking for a nic\n");
        setNic();
    } else {
        printf("Looks like the nic was preconfigured %d\n", atoi(pszArgs[1]));
        inicId = atoi(pszArgs[1]);
        //netPcap.setNetworkDevice(inicId);
        char* nicName="lo";
        netPcap.setNetworkDevice(inicId, nicName);//Use allways lo
    }
    
    //If there is an error with the nics
    if (inicId == -2) {
        return -1;
    }
    
    //Starting and forking threads
    //Simple cmd input
    while (istatus != 2) {
        runCapture();
        printf("> ");
        cin >> istatus;
        if (istatus == 0) {
            //Si ya esta corriento imprimir que ya esta corriendo
            //runCapture();
        } else if (istatus == 1) {
            restartAll();
        } else if (istatus < 0 && istatus > 2) {
            printf("Wrong command\n");
        }
    }

    //If threads are alive execute shutdown 
    shutdown();
    cout << "bye!";
}

void setNic() {
    //print nics
    while (inicId == -1) {
        netPcap.chooseNetworkDevice(inicId);
    }
}

void runCapture() {
    printf("Running analysis\n");
    netPcap.openNetworkDevice();
    //netPcap.run();
    netPcap.start();
    dispatcher.start();
}

void shutdown() {
    printf("Shutting down\n");
    dispatcher.countersBuffer.PrintAndRestartGrandTotal();
    netPcap.close();
    dispatcher.close();
}

void restartAll() {
    printf("restarting\n");
    shutdown();
}
