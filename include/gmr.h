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


    Col <double> priors;
    std::vector<vec> Mu;
    std::vector<mat> Sigma;
    mat x;  //clock signal as input
    span in;
    span out;

    GaussianDistribution pdf;
    Mat <double> expectedMu;


public:

    void Compute_GMR ( Col <double> _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, span _in, span _out);
    Mat <double >  returnExpectedMu();



};

#endif //PROGRAMMING_BY_DEMONSTRATION_GMR_H
