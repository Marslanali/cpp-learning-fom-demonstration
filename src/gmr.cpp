//
// Created by arslan on 16/11/19.
//

// GMR Source File

#include "/home/arslan/CLionProjects/cpp_learning_from_demonstration/include/gmr.h"
#include <iostream>
#include <fstream>


void GMR::Compute_GMR( Col <double> _priors, std::vector<vec> _Mu, std::vector<mat> _Sigma, mat _x, uint _in,  Col <double> _out)
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

    std::ofstream filePosition("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/Position.txt");

    const int in = 0;
    const span out(1, nbVars - 1);
    const int nb_var_out = out.b - out.a + 1;

    const float diag_reg_fact = 1e-8f;

    //mat mu_tmp = zeros(nb_var_out, nbStates);
    Mat <double> mu_tmp = zeros(nb_var_out, nbStates);


//    mat mat_priors;
 //   mat_priors = priors; // for making .* i.e % compatable in equation 1.1

    //-----------------------------------------------------------------------------
    // compute the infulence of each GMM component, given input x
    //-----------------------------------------------------------------------------

    //mat pxi = zeros(nbDataPoints, nbStates);
    Mat <double> pxi = zeros(nbDataPoints, nbStates);


    for (int i = 0; i < nbStates; ++i)
    {
        vec mu(1);
        mu(0) = Mu[i](in);

        Mat <double> sigma(1, 1);
        sigma(0, 0) = Sigma[i](in, in);

        pxi(span::all, i) = priors(i) * pdf.gaussPDF(x, mu, sigma);  // Equation 1.1 ....Error element wise muliplication is not working


    }

    Mat<double> beta = pxi / repmat(sum(pxi,1)+ DBL_MIN,1,nbStates);

    std::cout<<"beta :\n" <<beta<<std::endl;

    //-----------------------------------------------------------------------------
    // Compute expected means y, given input x
    //-----------------------------------------------------------------------------

    Cube <double> y_tmp(3,nbDataPoints,nbStates);  // output, dataPoints, nbStates

    for (int i = 0; i < nbStates; ++i)
    {

        vec mu1 (1);
        mu1(0)=Mu[i](in);

        Mat <double> sigma(1, 1);
        sigma(0, 0) = Sigma[i](in, in);  // for inverse sigma
        std::cout<<"SIZE Cube:\n"<<size(y_tmp)<<std::endl;
        //std::cout<<"Mu out:\n"<<Mu[i](out)<<std::endl;
       std::cout<< repmat(Mu[i](out).t(),1,nbDataPoints)<<std::endl;

        //y_tmp.slice(i) = repmat(Mu[i](out),1,nbDataPoints)+Sigma[i](out,in) * inv(sigma) *  (x - repmat(mu1,1,nbDataPoints));

        //  std::cout<<y_tmp.slice(i)<<std::endl;

    }

    const uword N = 1;
    const uword num_rows = nbDataPoints;
    const uword num_cols = nbStates;

    Cube<double> beta_tmp(num_rows,num_cols, 1);

    beta_tmp.slice(0) = beta;
    beta_tmp.reshape(1, nbDataPoints, nbStates);

    //std::cout << "Beta_TMP: "<< beta_tmp<<std::endl;
    //std::cout<<"Size beta_tmp"<<size(beta_tmp)<<"size y_Tmp: "<<size(y_tmp)<<std::endl;

    Cube<double> beta_tmp3(3,nbDataPoints,4);  //out,datapionts, states
    for (int i = 0; i < 3; ++i) {

        beta_tmp3.slice(i)=repmat(beta_tmp.slice(0),3,1);

    }

    //std::cout<<"beta_tmp3 size: "<<size(beta_tmp3)<<std::endl;
    Cube <double> y_tmp2 = beta_tmp3 % y_tmp;
    Mat <double > y = zeros (3,nbDataPoints);
    //beta_tmp3.slice(i)= repmat(beta_tmp.slice(1),3,1) % y_tmp;
    expectedMu = zeros (3,nbDataPoints);
    //y=sum(y_tmp,2);
    //std::cout<< "expected mean: "<< y <<std::endl;
    //std::cout<< "expected mean size: "<<size(y)<<std::endl;

    for (int i = 0; i < 200; ++i) {

        filePosition<<expectedMu(0,i)<<" "<<expectedMu(1,i)<<" "<<expectedMu(2,i)<<endl;

    }


    /*
    Cube<double> A(3, 5, 1, fill::randu);
    Cube<double> B(3, 5, 1, fill::randu);

    Mat<double> x = A.slice(0);
    Mat<double> y = B.slice(0);

    std::cout << "x:\n" << x << "\ny:\n" << y << std::endl;
    std::cout << "x*y:\n" << x%y << std::endl;
*/


}


Mat <double> GMR::returnExpectedMu()
{
    return expectedMu ;
}


/*
%% Compute expected means y, given input x
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for j=1:nbStates
  y_tmp(:,:,j) = repmat(Mu(out,j),1,nbData) + Sigma(out,in,j)*inv(Sigma(in,in,j)) * (x-repmat(Mu(in,j),1,nbData));
end
beta_tmp = reshape(beta,[1 size(beta)]);
y_tmp2 = repmat(beta_tmp,[length(out) 1 1]) .* y_tmp;
y = sum(y_tmp2,3);
%% Compute expected covariance matrices Sigma_y, given input x
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for j=1:nbStates
  Sigma_y_tmp(:,:,1,j) = Sigma(out,out,j) - (Sigma(out,in,j)*inv(Sigma(in,in,j))*Sigma(in,out,j));
end
beta_tmp = reshape(beta,[1 1 size(beta)]);
Sigma_y_tmp2 = repmat(beta_tmp.*beta_tmp, [length(out) length(out) 1 1]) .* repmat(Sigma_y_tmp,[1 1 nbData 1]);
Sigma_y = sum(Sigma_y_tmp2,4);
 */
