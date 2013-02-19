/* 
 * File:   DBData.h
 * Author: tuxtor
 *
 * Created on February 18, 2013, 6:20 PM
 */

#ifndef DBDATA_H
#define	DBDATA_H
#include<ctime>

class DBData {
public:
    DBData(int numActiveFilters);
    DBData(const DBData& orig);
    virtual ~DBData();
    void SetCounters(int* counters);
    int* GetCounters() const;
    void SetTsp(std::time_t tsp);
    std::time_t GetTsp() const;
private:
    std::time_t tsp;
    int* counters;
};

#endif	/* DBDATA_H */

