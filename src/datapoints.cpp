//
// Created by arslan on 16/11/19.
//


#include "../include/datapoints.h"

Datapoints::Datapoints(uint _nbVars, uint _nbPoints)
{
    nbVars = _nbVars;
    nbPoints = _nbPoints;
    data = zeros(_nbVars, _nbPoints);
}


mat Datapoints::getDataPoints()
{
    return data;
}

uint Datapoints::getNumVars()
{
    return nbVars;
}

uint Datapoints::getNumPoints()
{
    return nbPoints;
}

std::vector <std::string> Datapoints::getVarNames()
{

}

void Datapoints::setData(const mat& _data)
{
    data = _data;
    nbVars = data.n_rows;
    nbPoints = data.n_cols;
}

void Datapoints::loadFromFile(std::string path, bool is_transpose)
{
    mat data;
    data.load(path,  arma::raw_ascii);
    if(is_transpose)
        data = data.t();
    setData(data);


}


void Datapoints::saveInFile(std::string path)
{
    data.save(path, raw_ascii);
}
