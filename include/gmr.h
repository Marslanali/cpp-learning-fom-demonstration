//
// Created by arslan on 16/11/19.
//


#ifndef PROGRAMMING_BY_DEMONSTRATION_GMR_H
#define PROGRAMMING_BY_DEMONSTRATION_GMR_H

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/mvn.h"
#include <armadillo>
#include <vector>
using namespace arma;

class GMR
{
private:
    uint nbVars;
    uint nbStates;
    uint nbDataPoints;


    colvec priors;
    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    mat x;  //clock signal as input
    span in;
    span out;

    GaussianDistribution pdf;
    mat expectedMu;


public:

    void computeGmr ( const colvec& _priors, const std::vector<vec>& _Mu, const  std::vector<mat>& _Sigma, const mat& _x, span _in, span _out);
    mat  returnExpectedMu();



};

#endif //PROGRAMMING_BY_DEMONSTRATION_GMR_H
