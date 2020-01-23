//
// Created by arslan on 16/11/19.
//

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/EM_initilization.h"
void EM_Initilization::learnKmeans(const mat& _data, uint _nbStates)
{
    data = _data;
    nbStates = _nbStates;

    nbVars = _data.n_rows;
    nbDataPoints = _data.n_cols;

    // Initialization of Gaussian Mixture Model (GMM) parameters by clustering
    // the data into equal bins based on the first variable (time steps).
    const float diag_reg_fact = 1e-4f;

    vec timing_sep = linspace<vec>(data(0, 0), data(0, data.n_cols - 1), nbStates + 1);
    std::cout<<"Timming_sep: "<<timing_sep<<std::endl;
    Mu.clear();
    Sigma.clear();
    priors = vec(nbStates);


    for (unsigned int i = 0; i < nbStates; ++i)
    {
        uvec idtmp = find( (data(0, span::all) >= timing_sep(i)) && (data(0, span::all) < timing_sep(i + 1)) );

        //std::cout<<"\ndata ids: \n"<< i<<std::endl;

        priors(i) = idtmp.size();
        Mu.push_back(mean(data.cols(idtmp), 1));
        std::cout<<"Data Cols: "<<data.cols(idtmp).t()<<std::endl;

        mat sigma = cov(data.cols(idtmp).t(), data.cols(idtmp).t());
        std::cout<<"Sigma: "<<sigma<<std::endl;
        // Optional regularization term to avoid numerical instability
       // sigma = sigma + eye(nbVars, nbVars) * diag_reg_fact;

        Sigma.push_back(sigma);
    }


    priors = priors / sum(priors);


}


vec EM_Initilization::getPriors()
{
    return priors;

}

std::vector<vec> EM_Initilization::getMu()
{
    return Mu;

}

std::vector <mat> EM_Initilization::getSigma()
{
    return Sigma;
}

/*
    //**********************************************************************************************************************
    // kmeans clustering testing

    mat X1 = randu(100,2)*0.75+ones(100,2);
    mat X2 = randu(100,2)*0.5-ones(100,2);

    mat X = join_cols(X1,X2);

    std::cout<<"\n "<<X<<std::endl;
    std::cout<<X.n_rows<<std::endl;
    std::cout<<X.n_cols<<std::endl;

    std::vector<double> random_data_X;
    std::vector<double> random_data_Y;

    for (int i=0; i<X.n_rows; ++i)
    {
        random_data_X.push_back(X(i,0));
        random_data_Y.push_back(X(i,1));
    }

    plt::figure();
    plt::plot(random_data_X,random_data_Y,".");
    plt::title("Random Data");
    plt::show();

    //**********************************************************************************************************************
*/