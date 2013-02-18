/* 
 * File:   main.cpp
 * Author: tuxtor
 *
 * Created on February 14, 2013, 11:18 AM
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
//---
using namespace std;
#include "NetPcap.h"
//XML Scanner
//DataManager
NetPcap netPcap;
//ThreadDispatcher
int istatus;
int inicId = -1;

void runCapture();
void shutdown();
void restartAll();
void setNic();

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
        netPcap.setNetworkDevice(inicId);
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
    netPcap.run();
}

void shutdown() {
    printf("Shutting down\n");
    netPcap.close();
}

void restartAll() {
    printf("restarting\n");
}
