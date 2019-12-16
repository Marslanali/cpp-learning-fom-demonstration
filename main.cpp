//
// Created by arslan on 3/11/19.
//

#include <iostream>
#include <sstream>
#include "include/datapoints.h"
#include "include/EM_initilization.h"
#include "include/matplotlibcpp.h"
#include "include/gmm.h"
#include "include/gmr.h"

#define nbStates 4
#define nbVar 4
#define nbData 200

namespace plt = matplotlibcpp;
using namespace arma;

int main(int argc, char **argv)
{

    Datapoints positionData;

    positionData.loadFromFile("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/data_txyz.txt");

    std::cout<<"\n Data : \n "<< positionData.getDataPoints()<<std::endl;
    std::cout<<"\n nbVars : "<< positionData.getNumVars()<<std::endl;
    std::cout<<"\n nbDataPoints : "<< positionData.getNumPoints()<<std::endl;

    std::cout<<"\n Time is:\n "<<positionData.getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"\n Position X "<<positionData.getDataPoints()(1,span::all)<<std::endl;
    std::cout<<"\n Position Y "<<positionData.getDataPoints()(2,span::all)<<std::endl;
    std::cout<<"\n Position Z "<<positionData.getDataPoints()(3,span::all)<<std::endl;

    std::vector<double> time, positionX, positionY, positionZ;

    /*

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

     */

    EM_Initilization em_init_kmeans;
    em_init_kmeans.learnKmeans(positionData.getDataPoints(), nbStates);
/*
    std::cout<<"Priors : "<<em_init_kmeans.getPriors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans.getMu().size(); ++j)
        std::cout<<"\n Mu : \n"<<em_init_kmeans.getMu()[j]<<std::endl;

    for (int k = 0; k < em_init_kmeans.getSigma().size(); ++k)
        std::cout<<"\n Sigma :\n "<<em_init_kmeans.getSigma()[k]<<std::endl;
*/
    GMM gmm;
    gmm.EM(positionData.getDataPoints(), em_init_kmeans.getPriors(), em_init_kmeans.getMu(), em_init_kmeans.getSigma());

    std::cout<<"Final Priors are: "<<gmm.returnPriors()<<std::endl;
    for (int i =0; i<gmm.returnMu().size(); ++i)
       std::cout<<"Final Mu are :"<<gmm.returnMu()[i]<<std::endl;
    for (int i = 0; i < gmm.returnSigma().size() ; ++i)
       std::cout<<"Final Sigma are: "<<gmm.returnSigma()[i]<<std::endl;


    // GMR for expected mean and covariances
    mat clockSignal = linspace<vec>(0,2*datum::pi, positionData.getNumPoints());
    clockSignal = clockSignal.t();


    std::cout<<"Clock Signal  "<<clockSignal<<std::endl;

    /*

    std::vector<double> plotClock;

    for (int i = 0; i <positionData.getNumPoints() ; ++i)
        plotClock.push_back(clockSignal(0,i));


    plt::figure();
    plt::plot(plotClock);
    plt::show();

*/

    GMR gmr;
    gmr.Compute_GMR(gmm.returnPriors(), gmm.returnMu(), gmm.returnSigma(), clockSignal, 0, gmm.returnPriors());

    return 0;
}