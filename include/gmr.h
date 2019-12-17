//
// Created by arslan on 16/11/19.
//


#ifndef PROGRAMMING_BY_DEMONSTRATION_GMR_H
#define PROGRAMMING_BY_DEMONSTRATION_GMR_H

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/mvn.h"
#include "armadillo"
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
    Mat <double> expectedMu;


public:

    void Compute_GMR (vec _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, uint _in, vec _out);
    Mat <double >  returnExpectedMu();



};

#endif //PROGRAMMING_BY_DEMONSTRATION_GMR_H
