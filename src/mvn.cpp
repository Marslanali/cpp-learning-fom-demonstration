//
// Created by arslan on 16/11/19.
//

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/mvn.h"

vec GaussianDistribution::gaussPDF(mat _data, colvec _Mu, mat _Sigma)
{

    data = _data;
    Mu = _Mu;
    Sigma = _Sigma;

    nbVars = _data.n_rows;;
    nbDataPoints = _data.n_cols;

    data = data.t() - repmat(Mu.t(), nbDataPoints,1);
    vec prob = sum((data*inv(Sigma)) % data,1);
    prob = exp(-0.5*prob) / sqrt(pow(2*datum::pi,nbVars) * det(Sigma) + DBL_MIN);

    return prob;


}