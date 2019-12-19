//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_MVN_H
#define PROGRAMMING_BY_DEMONSTRATION_MVN_H

#include <stdio.h>
#include <armadillo>
#include <vector>
#include <cfloat>

using namespace arma;

class GaussianDistribution
{
private:

    uint nbVars;
    uint nbDataPoints;

    mat data;
    colvec Mu;
    mat Sigma;

public:

    vec gaussPDF(mat _data, colvec _Mu, mat _Sigma);

};

#endif //PROGRAMMING_BY_DEMONSTRATION_MVN_H
