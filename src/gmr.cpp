//
// Created by arslan on 16/11/19.
//

#include "/home/arslan/CLionProjects/programming_by_demonstration/include/gmr.h"
#include <iostream>

void GMR::Compute_GMR(vec _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, uint _in, vec _out)
{

    nbVars = _Mu.size();
    nbDataPoints = _x.n_cols;
    nbStates= _Sigma.size();

    priors = _priors;
    Mu = _Mu;
    Sigma = _Sigma;
    x = _x;
    in = _in;
    out = _out;


    const int in = 0;
    const span out(1, nbVars - 1);

    const int nb_var_out = out.b - out.a + 1;

    const float diag_reg_fact = 1e-8f;

    mat mu_tmp = zeros(nb_var_out, nbStates);


//    mat mat_priors;
 //   mat_priors = priors; // for making .* i.e % compatable in equation 1.1

    //-----------------------------------------------------------------------------
    // compute the infulence of each GMM component, given input x
    //-----------------------------------------------------------------------------

    mat pxi = zeros(nbDataPoints, nbStates);

    for (int i = 0; i < nbStates; ++i)
    {
        vec mu(1);
        mu(0) = Mu[i](in);

        mat sigma(1, 1);
        sigma(0, 0) = Sigma[i](in, in);

        pxi(span::all, i) = priors(i) * pdf.gaussPDF(x, mu, sigma);  // Equation 1.1 ....Error element wise muliplication is not working


    }

    mat beta = pxi / repmat(sum(pxi,1)+ DBL_MIN,1,nbStates);

    //std::cout<<"beta :" <<beta<<std::endl;

    //-----------------------------------------------------------------------------
    // Compute expected means y, given input x
    //-----------------------------------------------------------------------------

    for (int i = 0; i < nbStates; ++i)
    {

        vec mu1 (1);
        mu1(0)=Mu[i](in);

        mat sigma(1, 1);
        sigma(0, 0) = Sigma[i](in, in);  // for inverse sigma

        cube y_tmp(3,nbDataPoints,i);
        //y_tmp.slice(i) =repmat(Mu[i](out),1,nbDataPoints) + Sigma[i](out,in) * inv(sigma) *  (x - repmat(mu1,1,nbDataPoints));

       std::cout<<"dfd"<<std::endl;


    }





}

/*
for j=1:nbStates
        y_tmp(:,:,j) = repmat(Mu(out,j),1,nbData) + Sigma(out,in,j)*inv(Sigma(in,in,j)) * (x-repmat(Mu(in,j),1,nbData));
end
        beta_tmp = reshape(beta,[1 size(beta)]);
y_tmp2 = repmat(beta_tmp,[length(out) 1 1]) .* y_tmp;
y = sum(y_tmp2,3);

 */