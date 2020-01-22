//
// Created by arslan on 16/11/19.
//

/**
 * This class computer the gaussian distribution.

   Inputs -----------------------------------------------------------------
   o data:
   o Mu:
   o Sigma:

  Outputs ----------------------------------------------------------------
   o prob:    N array representing the computed probability density function

 *
 */

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/mvn.h"

vec GaussianDistribution::gaussPDF(const mat& _data, const colvec& _Mu, const mat& _Sigma)
{

    data = _data;
    Mu = _Mu;
    Sigma = _Sigma;

    nbVars = data.n_rows;;
    nbDataPoints = data.n_cols;

    data = data.t() - repmat(Mu.t(), nbDataPoints,1);
    vec prob = sum((data*inv(Sigma)) % data,1);
    prob = exp(-0.5*prob) / sqrt(pow(2*datum::pi,nbVars) * det(Sigma) + DBL_MIN);

    return prob;


}