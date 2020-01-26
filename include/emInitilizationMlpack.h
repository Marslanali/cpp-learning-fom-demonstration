//
// Created by arslan on 18/12/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
#define PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
#include <mlpack/methods/kmeans/kmeans.hpp>

using namespace mlpack::kmeans;

#include <armadillo>
#include <vector>


using namespace arma;

class EmInitilizationMlpack
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

    void learnKmeansMlpack(const mat& _data, uint _nbStates);
    void saveParamskmeans(const char filename []);

    colvec getPriors();
    std::vector<vec> getMu();
    std::vector<mat> getSigma();

};




#endif //PROGRAMMING_BY_DEMONSTRATION_EMINITILIZATIONMLPACK_H
