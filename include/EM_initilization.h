//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_EM_INITILIZATION_H
#define PROGRAMMING_BY_DEMONSTRATION_EM_INITILIZATION_H

#include <armadillo>
#include <vector>

using namespace arma;

class EM_Initilization
{
private:
    mat data;
    uint nbStates;

    uint nbVars;
    uint nbDataPoints;

    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    vec priors;

public:

    void learnKmeans(mat _data, uint _nbStates);

    vec getPriors();
    std::vector<vec> getMu();
    std::vector<mat> getSigma();

};

#endif //PROGRAMMING_BY_DEMONSTRATION_EM_INITILIZATION_H
