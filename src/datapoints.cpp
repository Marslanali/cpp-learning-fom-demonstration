//
// Created by arslan on 16/11/19.
//


#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/datapoints.h"

Datapoints::Datapoints(const uint& nbVars, const uint& nbPoints)
{
    this->nbVars = nbVars;
    this->nbPoints = nbPoints;
    data = zeros(this->nbVars, this->nbPoints);
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

void Datapoints::setData(const mat& data)
{
    this->data = data;
    nbVars     = data.n_rows;
    nbPoints   = data.n_cols;
}

void Datapoints::loadFromFile(std::string path, bool is_transpose)
{
    mat _data;
    _data.load(path,  arma::raw_ascii);
    if(is_transpose)
        _data = _data.t();
    setData(_data);


}


void Datapoints::saveInFile(std::string path)
{
    data.save(path, raw_ascii);
}
