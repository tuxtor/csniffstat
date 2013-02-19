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

