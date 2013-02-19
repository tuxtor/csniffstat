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

