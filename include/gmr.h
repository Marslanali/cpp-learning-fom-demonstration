//
// Created by arslan on 16/11/19.
//

/*
 This function performs Gaussian Mixture Regression (GMR), using the
parameters of a Gaussian Mixture Model (GMM). Given partial input data,
the algorithm computes the expected distribution for the resulting
dimensions. By providing temporal values as inputs, it thus outputs a
smooth generalized version of the data encoded in GMM, and associated
constraints expressed by covariance matrices.

Inputs -----------------------------------------------------------------
  o Priors:  1 x K array representing the prior probabilities of the K GMM
             components.
  o Mu:      D x K array representing the centers of the K GMM components.
  o Sigma:   D x D x K array representing the covariance matrices of the
             K GMM components.
  o x:       P x N array representing N datapoints of P dimensions.
  o in:      1 x P array representing the dimensions to consider as
             inputs.
  o out:     1 x Q array representing the dimensions to consider as
             outputs (D=P+Q).
Outputs ----------------------------------------------------------------
  o y:       Q x N array representing the retrieved N datapoints of
             Q dimensions, i.e. expected means.
  o Sigma_y: Q x Q x N array representing the N expected covariance
             matrices retrieved.

 */


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
