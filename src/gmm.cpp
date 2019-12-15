//
// Created by arslan on 16/11/19.
//
/*
 This Class learns the parameters of a Gaussian Mixture Model
 (GMM) using a recursive Expectation-Maximization (EM) algorithm, starting
 from an initial estimation of the parameters.


 Inputs -----------------------------------------------------------------
   o _data:    D x N array representing N datapoints of D dimensions.
   o _priors: 1 x K array representing the initial prior probabilities
              of the K GMM components.
   o _Mu:     D x K array representing the initial centers of the K GMM
              components.
   o _Sigma:  D x D x K array representing the initial covariance matrices
              of the K GMM components.
 Outputs ----------------------------------------------------------------
   o Priors:  1 x K array representing the prior probabilities of the K GMM
              components.
   o Mu:      D x K array representing the centers of the K GMM components.
   o Sigma:   D x D x K array representing the covariance matrices of the
              K GMM components.

*/

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/gmm.h"
#include <iostream>

void GMM::EM(mat _data, vec _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma)
{
    nbVars = _data.n_rows;
    nbDataPoints = _data.n_cols;
    nbStates= _Sigma.size();

    data = _data;
    Mu = _Mu;
    Sigma = _Sigma;
    priors = _priors;



    // Training of a Gaussian mixture model (GMM) with an expectation-maximization
    // (EM) algorithm
    const int nb_max_steps = 100;			// Maximum number of iterations allowed
    const int nb_min_steps = 5;				// Minimum number of iterations allowed
    const double max_diff_log_likelihood = 1e-4;	// Likelihood increase threshold
    // to stop the algorithm
    std::vector<double> log_likelihoods;

    int stepsCount=0;

    for (int iter = 0; iter < nb_max_steps; ++iter)
    {
        stepsCount += 1;
        //******************E-STEP************************************
        mat pxi = zeros(nbDataPoints, nbStates);

        for (int i = 0; i < nbStates; ++i)
        {
            //Compute probability p(x|i)
            pxi(span::all, i) = pdf.gaussPDF(data, Mu[i], Sigma[i]);
            //std::cout<<"This is pdf type checking: "<<pdf.gaussPDF(data,Mu[i],Sigma[i])<<std::endl;

        }
        //Compute posterior probability p(i|x)
        mat pix_tmp = repmat(priors.t(), nbDataPoints, 1) % pxi;
        mat pix = pix_tmp / repmat(sum(pix_tmp, 1), 1, nbStates);
        //compute cumulated posterior probability
        mat E = sum(pix);


        //*********************************M-Step***************************************

        for (int i = 0; i < nbStates; ++i)
        {
            //Update the priors
            priors[i] = E[i] / nbDataPoints;
            //Update the centers
            Mu[i] = data * pix(span::all, i) / E[i];
            // update the covariance matrices
            mat Data_tmp1 = data - repmat(Mu[i], 1, nbDataPoints);
            Sigma[i] = (repmat(pix(span::all, i).t(), nbVars, 1) % Data_tmp1 * Data_tmp1.t()) / E[i];
            // Add a tiny variance to avoid numerical instability
            Sigma[i] = Sigma[i] + eye(data.n_rows, data.n_rows) * diag_reg_fact;

        }

        // EM stopping criteria
        mat L = zeros(nbStates, data.n_cols);

        for (int i = 0; i < nbStates; ++i)
        {
            L(i, span::all) = priors(i) * mat(pdf.gaussPDF(data, Mu[i], Sigma[i])).t();
        }

        // Compute average log-likelihood
        log_likelihoods.push_back(vec(sum(log(sum(L, 0)), 1))[0] / data.n_cols);

        // Stop the algorithm if EM converged (small change of log-likelihood)
        if (iter >= nb_min_steps)
        {
            if (log_likelihoods[iter] - log_likelihoods[iter - 1] < max_diff_log_likelihood)
                break;
        }


    }

    std::cout<<"Total EM Steps are: "<<stepsCount<<std::endl;

}


vec GMM::returnPriors()
{
    return priors;
}

std::vector<vec> GMM::returnMu()
{
    return Mu;
}

std::vector<mat> GMM::returnSigma()
{
    return Sigma;
}