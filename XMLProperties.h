/* 
 * File:   XMLProperties.h
 * Author: tuxtor
 *
 * Created on February 17, 2013, 8:35 PM
 */

#ifndef XMLPROPERTIES_H
#define	XMLPROPERTIES_H

#include <iostream>
#include <cstring>
#include <cstdlib>
class XMLProperties {
public:
    XMLProperties();
    XMLProperties(const XMLProperties& orig);
    virtual ~XMLProperties();

    int GetSocketsPort() const {
        return socketsPort;
    }

    bool IsSocketsOn() const {
        return socketsOn;
    }

    std::string GetDbArchiveTableName() const {
        return dbArchiveTableName;
    }

    bool IsDbArchiveOn() const {
        return dbArchiveOn;
    }

    std::string GetDbFatName() const {
        return dbFatName;
    }

    bool IsDbFatOn() const {
        return dbFatOn;
    }

    std::string GetDbPassword() const {
        return dbPassword;
    }

    std::string GetDbUsername() const {
        return dbUsername;
    }

    std::string GetDbLocation() const {
        return dbLocation;
    }

    std::string GetDbPort() const {
        return dbPort;
    }

    std::string GetDbHostName() const {
        return dbHostName;
    }

    std::string GetDbName() const {
        return dbName;
    }

    int GetPortToFilter() const {
        return portToFilter;
    }

    int GetAmmountOfIntervals() const {
        return ammountOfIntervals;
    }

    int GetIntervalOfAnalysis() const {
        return intervalOfAnalysis;
    }

    
private:
    int intervalOfAnalysis;
    int ammountOfIntervals;
    int portToFilter;
    
    // Database related properties
    std::string dbName;
    std::string dbHostName;
    std::string dbPort;
    std::string dbLocation;
    std::string dbUsername;
    std::string dbPassword;
    bool dbFatOn;
    std::string dbFatName; // Fast Access Table = FAT
    bool dbArchiveOn;
    std::string dbArchiveTableName;
    
    // Socket related
    bool socketsOn;
    int socketsPort;
};

#endif	/* XMLPROPERTIES_H */

