//
// Created by arslan on 16/11/19.
//



/**
Copyright (C) 2014, Davide De Tommaso

This file is part of PbDLib.

    PbDLib is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    PbDLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with PbDLib.  If not, see <http://www.gnu.org/licenses/>.
*/

/*! \file datapoints.h
\brief Datapoints class
The class Datapoints allows to access samples of n-points and n-variables
stored in a Armadillo matrix.

\author Davide De Tommaso
\bug No known bugs.
*/

#ifndef PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H
#define PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H


#include "armadillo"
#include <fstream>
#include <vector>

using namespace arma;

class Datapoints
{
private:
    uint nbVars;
    uint nbPoints;
    std::vector<std::string> vars_names;
    mat data;

public:

    Datapoints(){};
    Datapoints(uint _nbVar , uint _nbPoints);

    mat getDataPoints();
    uint getNumPoints();
    uint getNumVars();
    std::vector <std::string> getVarNames();

    void setData(mat _data);
    void loadFromFile(std::string path, bool is_transpose = false);
    void saveInFile(std::string path);
};



#endif //PROGRAMMING_BY_DEMONSTRATION_DATAPOINTS_H



