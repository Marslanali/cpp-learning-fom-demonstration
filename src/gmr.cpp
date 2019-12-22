//
// Created by arslan on 16/11/19.
//

// GMR Source File

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/gmr.h"
#include <iostream>
#include <fstream>


void GMR::Compute_GMR( Col <double> _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, span _in, span _out)
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

    std::ofstream filePosition("/home/arslan/Arslan Ali/Arslan_Data/GMM-GMR-v2.0/data/Position.txt");

   // const int in = 0;
    //const span out(1, nbVars - 1);
    const int nb_var_out = out.b - out.a + 1;
    const float diag_reg_fact = 1e-8f;

    //mat mu_tmp = zeros(nb_var_out, nbStates);
    Mat <double> mu_tmp = zeros(nb_var_out, nbStates);

    //std::cout<<"input:\n"<<x<<std::endl;

    //-----------------------------------------------------------------------------
    // compute the infulence of each GMM component, given input x
    //-----------------------------------------------------------------------------

    //mat pxi = zeros(nbDataPoints, nbStates);
    Mat <double> pxi = zeros(nbDataPoints, nbStates);
    Col <double> PDF;


    for (int i = 0; i < nbStates; ++i)
    {
        Mat <double> sigma(1, 1);
        //std::cout<<"PDF\n"<<pdf.gaussPDF(x, Mu[i](in), Sigma[i](in,in))<<std::endl;
        //PDF = pdf.gaussPDF(x, Mu[i](in), Sigma[i](in,in));
        pxi(span::all, i) = priors(i) * pdf.gaussPDF(x, Mu[i](in), Sigma[i](in,in));  // Equation 1.1 ....Error element wise muliplication is not working

    }


    //std::cout<<"Pxi\n"<<pxi<<std::endl;
    //std::cout<<"DBL_MIN\n"<<DBL_MIN<<std::endl;

    Mat<double> beta = pxi / repmat(sum(pxi,1)+ DBL_MIN,1,nbStates);

    //std::cout<<"beta:\n" <<beta<<std::endl;

    //-----------------------------------------------------------------------------
    // Compute expected means y, given input x
    //-----------------------------------------------------------------------------

    Cube <double> y_tmp(nb_var_out,nbDataPoints,nbStates);  // output, dataPoints, nbStates

    for (int i = 0; i < nbStates; ++i)
        y_tmp.slice(i) = repmat(Mu[i](out),1,nbDataPoints) + Sigma[i](out,in) * inv (Sigma[i](in,in)) * (x - repmat(Mu[i](in),1,nbDataPoints));

    const uword N = 1;
    const uword num_rows = nbDataPoints;
    const uword num_cols = nbStates;

    Cube<double> beta_tmp(num_rows, num_cols, 1);

    beta_tmp.slice(0) = beta;
    beta_tmp.reshape(1, nbDataPoints, nbStates);

   // std::cout << "beta_tmp:\n"<< beta_tmp<<std::endl;
    //std::cout<<"Size beta\n"<<size(beta)<<"\nsize beta_tmp:\n"<<size(beta_tmp)<<std::endl;

    Cube<double> beta_tmp2(nb_var_out,nbDataPoints,nbStates);  //out,datapionts, states
    for (int i = 0; i < nbStates; ++i) {

        beta_tmp2.slice(i)=repmat(beta_tmp.slice(0),3,1);

    }

    //std::cout<<"beta_tmp3 size: "<<size(beta_tmp3)<<std::endl;
   // Cube <double> y_tmp2 (nb_var_out, nbDataPoints, nbStates);
    Cube <double> y_tmp2  = beta_tmp2 % y_tmp;
    //std::cout<<"\ny_tmp2\n"<<y_tmp2<<std::endl;
   // Mat <double > y = zeros (nb_var_out,nbDataPoints);
    //beta_tmp3.slice(i)= repmat(beta_tmp.slice(1),3,1) % y_tmp;
    expectedMu = zeros (nb_var_out,nbDataPoints);
    //std::cout<< "expected mean: "<< y <<std::endl;
    //std::cout<< "expected mean size: "<<size(y)<<std::endl;
    //mat y = randu<mat>(2,2);
    //mat y1=sum(y,0);
    //std::cout<<"input\n"<<y<<"\noutput\n"<<y1<<std::endl;

    std::vector <double> s1;
    std::vector <double> s2;
    std::vector <double> s3;


    for (int i = 0; i < nbDataPoints; ++i) {
        s1.push_back(y_tmp2.slice(0)(0,i) + y_tmp2.slice(1)(0,i));
        s2.push_back(y_tmp2.slice(0)(1,i) + y_tmp2.slice(1)(1,i));
        s3.push_back(y_tmp2.slice(0)(2,i) + y_tmp2.slice(1)(2,i));
    }

    for (int j = 0; j < 200 ; ++j)
    std::cout<<"Sumis \n"<<s1[j]<<std::endl;



    for (int i = 0; i < 200; ++i) {

        filePosition<<s1[i]<<std::endl;

    }


}


Mat <double> GMR::returnExpectedMu()
{
    return expectedMu ;
}
