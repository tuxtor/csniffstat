/* 
 * File:   DBData.cpp
 * Author: tuxtor
 * 
 * Created on February 18, 2013, 6:20 PM
 */

#include "DBData.h"

DBData::DBData(int numActiveFilters) {
    counters = new int[numActiveFilters];
}

DBData::DBData(const DBData& orig) {
}

DBData::~DBData() {
}

void DBData::SetCounters(int* counters) {
    this->counters = counters;
}

int* DBData::GetCounters() const {
    return counters;
}

void DBData::SetTsp(std::time_t tsp) {
    this->tsp = tsp;
}

std::time_t DBData::GetTsp() const {
    return tsp;
}

