//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_GMM_H
#define PROGRAMMING_BY_DEMONSTRATION_GMM_H

#include "armadillo"
#include "/home/arslan/CLionProjects/programming_by_demonstration/include/mvn.h"
#include <vector>

using namespace arma;

class GMM
{
private:
    uint nbVars;
    uint nbStates;
    uint nbDataPoints;

    mat data;
    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    vec priors;

    const float diag_reg_fact = 1e-4f;

    std::vector<GaussianDistribution> PDF;
    GaussianDistribution pdf;

public:

    void EM(mat _data, vec _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma);
    vec returnPriors ();
    std::vector<vec> returnMu();
    std::vector<mat> returnSigma();


};


#endif //PROGRAMMING_BY_DEMONSTRATION_GMM_H
