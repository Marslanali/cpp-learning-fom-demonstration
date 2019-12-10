//
// Created by arslan on 16/11/19.
//


#ifndef PROGRAMMING_BY_DEMONSTRATION_GMR_H
#define PROGRAMMING_BY_DEMONSTRATION_GMR_H

#include "armadillo"
#include "/home/arslan/CLionProjects/programming_by_demonstration/include/mvn.h"
#include <vector>

using namespace arma;

class GMR
{
private:
    uint nbVars;
    uint nbStates;
    uint nbDataPoints;
    uint in;


    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    vec priors;
    mat x;  //clock signal as input
    vec out;

    GaussianDistribution pdf;


public:

    void Compute_GMR (vec _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, uint _in, vec _out);


};

#endif //PROGRAMMING_BY_DEMONSTRATION_GMR_H
