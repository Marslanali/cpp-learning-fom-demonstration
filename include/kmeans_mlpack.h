//
// Created by arslan on 18/12/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_KMEANS_MLPACK_H
#define PROGRAMMING_BY_DEMONSTRATION_KMEANS_MLPACK_H
#include <mlpack/methods/kmeans/kmeans.hpp>

using namespace mlpack::kmeans;

#include <armadillo>
#include <vector>


using namespace arma;

class EM_Initilization_MLPACK
{
private:
    mat data;
    uint nbStates;
    uint nbVars;
    uint nbDataPoints;

    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    colvec Priors;

public:

    void learnKmeans_mlpack(const mat& _data, uint _nbStates);
    void saveParams_kmeans(const char filename []);

    colvec getPriors();
    std::vector<vec> getMu();
    std::vector<mat> getSigma();

};




#endif //PROGRAMMING_BY_DEMONSTRATION_KMEANS_MLPACK_H
