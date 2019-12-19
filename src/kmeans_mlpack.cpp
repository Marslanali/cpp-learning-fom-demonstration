//
// Created by arslan on 18/12/19.
//

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/kmeans_mlpack.h"

void EM_Initilization_MLPACK::learnKmeans_mlpack(mat _data, uint _nbStates)
{
    data = _data;
    nbStates = _nbStates;

    nbVars = _data.n_rows;
    nbDataPoints = _data.n_cols;

    // Initialization of Gaussian Mixture Model (GMM) parameters by clustering
    // the data into equal bins based on the first variable (time steps).
    const float diag_reg_fact = 1e-4f;
   // vec timing_sep = linspace<vec>(data(0, 0), data(0, data.n_cols - 1), nbStates + 1);
    Mu.clear();
    Sigma.clear();
   // Priors.clear();



    // The dataset we are clustering.
   // mat data;
// The number of clusters we are getting.
    size_t clusters = nbStates;
// The assignments will be stored in this vector.
    Row <size_t> assignments;
// The centroids will be stored in this matrix.
    Mat <double> centroids;
// Initialize with the default arguments.
    KMeans<> k;
    k.Cluster(data, clusters, assignments, centroids);

    //std::cout<<"Assignments : "<<assignments<<std::endl;
   // std::cout<<"Centroids: "<<centroids<<std::endl;

    uvec idtmp;
    Col <double> priors (nbStates);

    for (int i = 0; i < nbStates; ++i)
    Mu.push_back(centroids(span::all,i));

    //std::cout<<"Means:\n"<<centroids<<std::endl;

    for (int i = 0; i < nbStates; ++i)
    {
        idtmp = find(assignments==i);
        //std::cout<<"\n IDTMP: \n "<<idtmp.n_elem<<std::endl;
        priors(i) = idtmp.n_elem;
       // std::cout<<"\n KMEANS Priors: \n "<< priors(i)<<std::endl;
       // std::cout<<"\n Data for specific Index: \n "<<data.cols(idtmp).t()<<std::endl;

        mat sigma = cov(data.cols(idtmp).t());
        //std::cout<<"Covariances Matrices:\n"<<sigma<<std::endl;
        // Optional regularization term to avoid numerical instability
        sigma = sigma + eye(nbVars, nbVars) * diag_reg_fact;

        Sigma.push_back(sigma);
    }

    Priors = priors / sum(priors);
   // std::cout<<"Overall Priors:\n"<<priors<<std::endl;
    //std::cout<<"Priors Sum: "<< sum(priors)<<std::endl;



}


Col <double> EM_Initilization_MLPACK::getPriors()
{
    return Priors;

}

std::vector<vec> EM_Initilization_MLPACK::getMu()
{
    return Mu;

}

std::vector <mat> EM_Initilization_MLPACK::getSigma()
{
    return Sigma;
}


void EM_Initilization_MLPACK::saveParams_kmeans(const char filename [])
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