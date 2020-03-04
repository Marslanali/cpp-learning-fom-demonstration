//
// Created by arslan on 18/12/19.
//

/**
 * This class implements kmeans clustering algorithm using C++ MLPACK Libraray

 Inputs -----------------------------------------------------------------
   o data:     D x N array representing N datapoints of D dimensions.
   o nbStates: D representing the K GMM components.

 Outputs ----------------------------------------------------------------
   o priors:  Q x N array representing the retrieved N datapoints of
              Q dimensions, i.e. expected means.
   o Mu:      Q x Q x N array representing the N expected covariance
              matrices retrieved.
   o Sigma:   Q x Q x N array representing the N expected covariance
              matrices retrieved.

 */

#include "../include/emInitilizationMlpack.h"

void EmInitilizationMlpack::learnKmeansMlpack(const mat& _data, uint _nbStates)
{
    // The dataset we are clustering.
    data = _data;

    nbStates = _nbStates;
    nbVars = _data.n_rows;
    nbDataPoints = _data.n_cols;

    // Initialization of Gaussian Mixture Model (GMM) parameters by clustering
    // the data into equal bins based on the first variable (time steps).
    const float diag_reg_fact = 1e-4f;

    Mu.clear();
    Sigma.clear();
    Priors.clear();

    // The number of clusters we are getting.
    size_t clusters = nbStates;
    // The assignments will be stored in this vector.
    Row <size_t> assignments;
    // The centroids will be stored in this matrix.
    Mat <double> centroids;
    // Initialize with the default arguments.
    KMeans<> k;
    k.Cluster(data, clusters, assignments, centroids);

    std::cout<<"Assignments:\n"<<assignments<<std::endl;
    std::cout<<"Centroids:\n"<<centroids<<std::endl;

    uvec idtmp;
    Col <double> priors (nbStates);

    for (int i = 0; i < nbStates; ++i)
    Mu.push_back(centroids(span::all,i));

    for (int i = 0; i < nbStates; ++i)
    {
        idtmp = find(assignments==i);
        std::cout<<"\n IDTMP: \n "<<idtmp.n_elem<<std::endl;
        priors(i) = idtmp.n_elem;
        std::cout<<"\n KMEANS Priors: \n "<< priors(i)<<std::endl;
        std::cout<<"\n Data for specific Index: \n "<<data.cols(idtmp).t()<<std::endl;

        mat sigma = cov(data.cols(idtmp).t());
        std::cout<<"Covariances Matrices:\n"<<sigma<<std::endl;

/*
        try {

            if(sigma.n_rows==nbVars && sigma.n_cols==nbVars)
                // Optional regularization term to avoid numerical instability
                sigma = sigma + eye(nbVars, nbVars) * diag_reg_fact;

           else
                throw "Something went wrong Sigma Error!!!!!!\n";

        }

        catch(char const * e) {
            sigma = eye(nbVars, nbVars) * diag_reg_fact;
            cout << "Error message: " << e << endl;
        }

*/

        if(sigma.n_rows==nbVars && sigma.n_cols==nbVars)
                // Optional regularization term to avoid numerical instability
                sigma = sigma + eye(nbVars, nbVars) * diag_reg_fact;


        else {
            std::cout << "\n Something went wrong Sigma Error!!!!!!\n" << std::endl;
            sigma = eye(nbVars, nbVars) * diag_reg_fact;
        }

        Sigma.push_back(sigma);
    }

    Priors = priors / sum(priors);
    // std::cout<<"Overall Priors:\n"<<priors<<std::endl;
    //std::cout<<"Priors Sum:\n"<< sum(priors)<<std::endl;

}


Col <double> EmInitilizationMlpack::getPriors()
{
    return Priors;

}

std::vector<vec> EmInitilizationMlpack::getMu()
{
    return Mu;

}

std::vector <mat> EmInitilizationMlpack::getSigma()
{
    return Sigma;
}


void EmInitilizationMlpack::saveParamskmeans(const char filename [])
{/*
    // save the current kmeans parameters, coefficents to a file, to be retrieved
    // by the loadParams method
    std::ofstream file(filename);
    file << dim << " ";
    file << nbStates << std::endl;
    for(int i=0;i<nbStates;i++) file << priors[i] << " ";
    file << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            file << mu(s,i) << " ";
        }
        file << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                file << sigma[s](i,j) << " ";
            }
            file << std::endl;
        }
    }
    */
}