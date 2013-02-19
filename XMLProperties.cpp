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

#include "XMLProperties.h"
using namespace std;

XMLProperties::XMLProperties() {
    portToFilter = 8999;
}

XMLProperties::XMLProperties(const XMLProperties& orig) {
}

XMLProperties::~XMLProperties() {
}
