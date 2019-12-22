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

#define nbStates 10
#define nbVar 4
#define nbData 200

namespace plt = matplotlibcpp;
using namespace mlpack::kmeans;
using namespace arma;


int main(int argc, char **argv)
{


    Datapoints positionData;

    positionData.loadFromFile("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/input_data/data_xy.txt");

    std::cout<<"Data :\n"<< positionData.getDataPoints()<<std::endl;
    std::cout<<"nbVars :\n"<< positionData.getNumVars()<<std::endl;
    std::cout<<"nbDataPoints :\n"<< positionData.getNumPoints()<<std::endl;

    //std::cout<<"Time: "<<positionData.getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"Position X\n"<<positionData.getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"Position Y\n"<<positionData.getDataPoints()(1,span::all)<<std::endl;
    //std::cout<<"Position Z\n"<<positionData.getDataPoints()(2,span::all)<<std::endl;

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

    const span in(0);
    const span out(1, positionData.getNumVars() - 1);


    GMR gmr;
    //gmr.Compute_GMR(gmm.returnPriors(), gmm.returnMu(), gmm.returnSigma(), clockSignal,in, out);

    std::cout<<"Expected Mean: "<<gmr.returnExpectedMu()<<std::endl;
    std::cout<<"Expected Mean Size: "<<size(gmr.returnExpectedMu())<<std::endl;



    /*
    std::ofstream filekmeans_mu("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/kmeans_mu.txt");
    std::ofstream filekmeans_sigma("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/kmeans_sigma.txt");
    std::ofstream fileGMM_mu("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/gmm_mu.txt");
    std::ofstream fileGMM_sigma("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/gmm_sigma.txt");
    std::ofstream fileGMR_mu("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/gmr_mu.txt");
    std::ofstream fileGMR_sigma("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/gmr_sigma.txt");

*/


    int dim = 2;


    // save the current kmeans parameters

    std::ofstream fileKmeans("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/kmeans/kmeans.txt");
    //file << 2 << " ";
    //file << nbStates << std::endl;
    for(int i=0;i<nbStates;i++)
        fileKmeans << em_init_kmeans_mlpack.getPriors()[i] << " ";
    fileKmeans << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            fileKmeans << em_init_kmeans_mlpack.getMu()[s](i) << " ";
        }
        fileKmeans << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                fileKmeans << em_init_kmeans_mlpack.getSigma()[s](i,j) << " ";
            }
            fileKmeans << std::endl;
        }
    }




    // save the current gmm parameters

    std::ofstream fileGMM("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/gmm/gmm.txt");
    //file << 2 << " ";
    //file << nbStates << std::endl;
    for(int i=0;i<nbStates;i++)
        fileGMM << gmm.returnPriors()[i] << " ";
    fileGMM << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            fileGMM << gmm.returnMu()[s](i) << " ";
        }
        fileGMM << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                fileGMM << gmm.returnSigma()[s](i,j) << " ";
            }
            fileGMM << std::endl;
        }
    }

/*
    // save the current gmr parameters

    std::ofstream fileGMR("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/gmr/gmr.txt");
    //file << 2 << " ";
    //file << nbStates << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            fileGMR << gmr.returnExpectedMu()[s](i) << " ";
        }
        fileGMR << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                fileGMR << gmr.returnExpectedSigma()[s](i,j) << " ";
            }
            fileGMR << std::endl;
        }
    }

*/

    std::vector<double> time, positionX, positionY, positionZ;
    std::vector<double>  px, py, pz;
    std::vector<double>  plotClock;


    for (int i = 0; i <positionData.getNumPoints() ; ++i)
    {

    //    time.push_back(positionData.getDataPoints()(0,i));
        positionX.push_back(positionData.getDataPoints()(0,i));
        positionY.push_back(positionData.getDataPoints()(1,i));
      //  positionZ.push_back(positionData.getDataPoints()(3,i));

    }

    for (int i = 0; i <gmr.returnExpectedMu().n_cols ; ++i)
    {
        px.push_back(gmr.returnExpectedMu()(0,i));
        py.push_back(gmr.returnExpectedMu()(1,i));
        //pz.push_back(gmr.returnExpectedMu()(2,i));
    }


    for (int i = 0; i <positionData.getNumPoints() ; ++i)
        plotClock.push_back(clockSignal(0,i));

    plt::figure();
    plt::plot(plotClock);
    plt::save("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/input_clock.jpg");
    plt::show();

    std::vector <double> x,y;

    for (int i = 0; i <nbStates ; ++i) {
        x.push_back(gmm.returnMu()[i](0));
        y.push_back(gmm.returnMu()[i](1));
    }

    plt::figure();
    plt::stem(x,y,".*");
    plt::save("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/centroids_gmm.jpg");
    plt::show();

    plt::plot(positionX,positionY,"red");
    plt::save("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/input_data.jpg");
    plt::show();

    plt::figure();
    plt::subplot(2,1,1);
    //plt::plot(time,"red");
   // plt::subplot(2,2,2);
    plt::plot(positionX,"red");
    plt::subplot(2,1,2);
    plt::plot(positionY,"red");
    //plt::subplot(2,2,4);
    //plt::plot(positionZ,"red");
    plt::show();

    //plt::figure();
    //plt::plot(px,"green");
    //plt::show();

    return 0;
}
