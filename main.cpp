//
// Created by arslan on 3/11/19.
//
#include <iostream>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <sstream>
#include <fstream>
#include "include/datapoints.h"
#include "include/EM_initilization.h"
#include "include/kmeans_mlpack.h"
#include "include/matplotlibcpp.h"
#include "include/gmm.h"
#include "include/gmr.h"

#define nbStates 5
#define nbVar 4
#define nbData 200

namespace plt = matplotlibcpp;
using namespace mlpack::kmeans;
using namespace arma;


int main(int argc, char **argv)
{


    Datapoints positionData;

    positionData.loadFromFile("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/data_txyz.txt");

    std::cout<<"Data :\n"<< positionData.getDataPoints()<<std::endl;
    std::cout<<"nbVars : "<< positionData.getNumVars()<<std::endl;
    std::cout<<"nbDataPoints : "<< positionData.getNumPoints()<<std::endl;

    std::cout<<"Time: "<<positionData.getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"Position X "<<positionData.getDataPoints()(1,span::all)<<std::endl;
    std::cout<<"Position Y "<<positionData.getDataPoints()(2,span::all)<<std::endl;
    std::cout<<"Position Z "<<positionData.getDataPoints()(3,span::all)<<std::endl;

    std::ofstream filekmeans("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/kmeans.txt");


    EM_Initilization_MLPACK em_init_kmeans_mlpack;
    em_init_kmeans_mlpack.learnKmeans_mlpack(positionData.getDataPoints(), nbStates);


    std::cout<<"Priors Kmeans MLPACK :\n"<<em_init_kmeans_mlpack.getPriors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans_mlpack.getMu().size(); ++j)
        std::cout << "Mu Kmeans MLPACK:\n" << em_init_kmeans_mlpack.getMu()[j] << std::endl;

    for (int k = 0; k < em_init_kmeans_mlpack.getSigma().size(); ++k)
        std::cout<<"Sigma Kmeans MLPACK:\n"<<em_init_kmeans_mlpack.getSigma()[k]<<std::endl;

    /*

    EM_Initilization em_init_kmeans;
    em_init_kmeans.learnKmeans(positionData.getDataPoints(), nbStates);

    std::cout<<"Priors : "<<em_init_kmeans.getPriors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans.getMu().size(); ++j)
        std::cout << "\n Mu : \n" << em_init_kmeans.getMu()[j] << std::endl;

    for (int k = 0; k < em_init_kmeans.getSigma().size(); ++k)
        std::cout<<"\n Sigma :\n "<<em_init_kmeans.getSigma()[k]<<std::endl;
*/

    GMM gmm;
    gmm.EM(positionData.getDataPoints(), em_init_kmeans_mlpack.getPriors(), em_init_kmeans_mlpack.getMu(), em_init_kmeans_mlpack.getSigma());

       std::cout<<"Final Priors are:\n"<<gmm.returnPriors()<<std::endl;
    for (int i =0; i<gmm.returnMu().size(); ++i)
       std::cout<<"Final Mu are :\n"<<gmm.returnMu()[i]<<std::endl;
    for (int i = 0; i < gmm.returnSigma().size() ; ++i)
       std::cout<<"Final Sigma are:\n"<<gmm.returnSigma()[i]<<std::endl;


    // GMR for expected mean and covariances
    mat clockSignal = linspace<vec>(min(positionData.getDataPoints()(0,span::all)),max(positionData.getDataPoints()(0,span::all)), positionData.getNumPoints());
    clockSignal = clockSignal.t();


    std::cout<<"Clock Signal  "<<clockSignal<<std::endl;

/*
    GMR gmr;
    gmr.Compute_GMR(gmm.returnPriors(), gmm.returnMu(), gmm.returnSigma(), clockSignal, 0, gmm.returnPriors());

    std::cout<<"Expected Mean: "<<gmr.returnExpectedMu()<<std::endl;
    std::cout<<"Expected Mean Size: "<<size(gmr.returnExpectedMu())<<std::endl;


    std::vector<double> plotClock;

    for (int i = 0; i <positionData.getNumPoints() ; ++i)
        plotClock.push_back(clockSignal(0,i));


    plt::figure();
    plt::plot(plotClock);
    plt::show();


    std::vector<double> time, positionX, positionY, positionZ;


    for (int i = 0; i <positionData.getNumPoints() ; ++i)
    {

        time.push_back(positionData.getDataPoints()(0,i));
        positionX.push_back(positionData.getDataPoints()(1,i));
        positionY.push_back(positionData.getDataPoints()(2,i));
        positionZ.push_back(positionData.getDataPoints()(3,i));


    }

    plt::figure();
    plt::subplot(2,2,1);
    plt::plot(time,"red");
    plt::subplot(2,2,2);
    plt::plot(positionX);
    plt::subplot(2,2,3);
    plt::plot(positionY);
    plt::subplot(2,2,4);
    plt::plot(positionZ);
    plt::show();


    std::vector<double>  px, py, pz;

    for (int i = 0; i <gmr.returnExpectedMu().n_cols ; ++i)
    {

        px.push_back(gmr.returnExpectedMu()(0,i));
        py.push_back(gmr.returnExpectedMu()(1,i));
        pz.push_back(gmr.returnExpectedMu()(2,i));


    }

    plt::figure();
    plt::subplot(2,2,2);
    plt::plot(px);
    plt::subplot(2,2,3);
    plt::plot(py);
    plt::subplot(2,2,4);
    plt::plot(pz);
    plt::show();

*/

    return 0;
}
