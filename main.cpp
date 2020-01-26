//
// Created by arslan on 3/11/19.
//

/**
 * @author: Arslan Ali
 * @email: arslanali800@hotmail.com
 *
 * C++ Implementation of gaussian mixture model and gaussain mixture regression for learning 3-dof
 * task. The data set contains mutliple demonstrations of the task which are trained using gaussian
 * mixture model. Gaussian Mixture Regression had been used for generating single generalized trajectory
 * with expected mean and expected covariance matrices.The learned generalized trajectory is exectued on
 * the robot using simple PD controller.The algorithm is tested on 3-degree freedom phantom premium robot.
 *
 */
#include <iostream>
#include <mlpack/methods/kmeans/kmeans.hpp>
#include <sstream>
#include <fstream>
#include "include/datapoints.h"
#include "emInitilization.h"
#include "emInitilizationMlpack.h"
#include "include/matplotlibcpp.h"
#include "include/gmm.h"
#include "include/gmr.h"

#define nbStates 4
#define nbVar 4
#define nbData 200

namespace plt = matplotlibcpp;
using namespace mlpack::kmeans;
using namespace arma;


int main(int argc, char **argv)
{


    Datapoints* positionData = new Datapoints();

    //Load dataset containing cartesian position of the robot

    positionData->loadFromFile("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/input_data/data_xy.txt");

    std::cout<<"Data :\n"<< positionData->getDataPoints()<<std::endl;
    std::cout<<"nbVars :\n"<< positionData->getNumVars()<<std::endl;
    std::cout<<"nbDataPoints :\n"<< positionData->getNumPoints()<<std::endl;

    //std::cout<<"Time: "<<positionData.getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"Position X\n"<<positionData->getDataPoints()(0,span::all)<<std::endl;
    std::cout<<"Position Y\n"<<positionData->getDataPoints()(1,span::all)<<std::endl;
    //std::cout<<"Position Z\n"<<positionData.getDataPoints()(2,span::all)<<std::endl;

    // Initial estimation of the parameters using kmeans algorithm

    EmInitilizationMlpack* em_init_kmeans_mlpack = new EmInitilizationMlpack();
    em_init_kmeans_mlpack->learnKmeansMlpack(positionData->getDataPoints(), nbStates);


    /**
     * print learned priors, means and covarainces matrices
     */

    std::cout<<"Priors Kmeans MLPACK :\n"<<em_init_kmeans_mlpack->getPriors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans_mlpack->getMu().size(); ++j)
        std::cout << "Mu Kmeans MLPACK:\n" << em_init_kmeans_mlpack->getMu()[j] << std::endl;

    for (int k = 0; k < em_init_kmeans_mlpack->getSigma().size(); ++k)
        std::cout<<"Sigma Kmeans MLPACK:\n"<<em_init_kmeans_mlpack->getSigma()[k]<<std::endl;

    /*

    EM_Initilization em_init_kmeans;
    em_init_kmeans.learnKmeans(positionData.getDataPoints(), nbStates);

    std::cout<<"Priors : "<<em_init_kmeans.getPriors().t()<<std::endl;

    for (int j = 0; j < em_init_kmeans.getMu().size(); ++j)
        std::cout << "\n Mu : \n" << em_init_kmeans.getMu()[j] << std::endl;

    for (int k = 0; k < em_init_kmeans.getSigma().size(); ++k)
        std::cout<<"\n Sigma :\n "<<em_init_kmeans.getSigma()[k]<<std::endl;
*/


    // Final estimation of the parameters using gaussian mixture model

    GMM* gmm = new GMM();
    gmm->EM(positionData->getDataPoints(), em_init_kmeans_mlpack->getPriors(), em_init_kmeans_mlpack->getMu(), em_init_kmeans_mlpack->getSigma());

       std::cout<<"Final Priors are:\n"<<gmm->returnPriors()<<std::endl;
    for (int i =0; i<gmm->returnMu().size(); ++i)
       std::cout<<"Final Mu are :\n"<<gmm->returnMu()[i]<<std::endl;
    for (int i = 0; i < gmm->returnSigma().size() ; ++i)
       std::cout<<"Final Sigma are:\n"<<gmm->returnSigma()[i]<<std::endl;


    /**
     * GMR for expected mean and covariances
     * we can get learned generalized trajectory using Gaussian Mixture Regression which time variable
     * as an input and mean, covariance matrix as ouptut. The time variable can be generated using linspace
     */
    mat clockSignal = linspace<vec>(min(positionData->getDataPoints()(0,span::all)),max(positionData->getDataPoints()(0,span::all)), positionData->getNumPoints());
    clockSignal = clockSignal.t();

    std::cout<<"Clock Signal  "<<clockSignal<<std::endl;

    const span in(0);
    const span out(1, positionData->getNumVars() - 1);

    /**
     * computing GMR with time variable as input
     */

    GMR* gmr = new GMR();
    //gmr.Compute_GMR(gmm.returnPriors(), gmm.returnMu(), gmm.returnSigma(), clockSignal,in, out);

    std::cout<<"Expected Mean: "<<gmr->returnExpectedMu()<<std::endl;
    std::cout<<"Expected Mean Size: "<<size(gmr->returnExpectedMu())<<std::endl;



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
        fileKmeans << em_init_kmeans_mlpack->getPriors()[i] << " ";
    fileKmeans << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            fileKmeans << em_init_kmeans_mlpack->getMu()[s](i) << " ";
        }
        fileKmeans << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                fileKmeans << em_init_kmeans_mlpack->getSigma()[s](i,j) << " ";
            }
            fileKmeans << std::endl;
        }
    }




    // save the current gmm parameters

    std::ofstream fileGMM("/home/arslan/CLionProjects/cpp_learning_from_demonstration/data/gmm/gmm.txt");
    //file << 2 << " ";
    //file << nbStates << std::endl;
    for(int i=0;i<nbStates;i++)
        fileGMM << gmm->returnPriors()[i] << " ";
    fileGMM << std::endl;
    for(int s=0;s<nbStates;s++) {
        for(int i=0;i<dim;i++) {
            fileGMM << gmm->returnMu()[s](i) << " ";
        }
        fileGMM << std::endl;
    }
    for(int s=0;s<nbStates;s++) {
        for(int j=0;j<dim;j++) {
            for(int i=0;i<dim;i++) {
                fileGMM << gmm->returnSigma()[s](i,j) << " ";
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


    for (int i = 0; i <positionData->getNumPoints() ; ++i)
    {

        // time.push_back(positionData.getDataPoints()(0,i));
        positionX.push_back(positionData->getDataPoints()(0,i));
        positionY.push_back(positionData->getDataPoints()(1,i));
        //  positionZ.push_back(positionData.getDataPoints()(3,i));

    }

    for (int i = 0; i <gmr->returnExpectedMu().n_cols ; ++i)
    {
        px.push_back(gmr->returnExpectedMu()(0,i));
        py.push_back(gmr->returnExpectedMu()(1,i));
        //pz.push_back(gmr.returnExpectedMu()(2,i));
    }


    for (int i = 0; i <positionData->getNumPoints() ; ++i)
        plotClock.push_back(clockSignal(0,i));

    plt::figure();
    plt::plot(plotClock);
    plt::save("/home/arslan/CLionProjects/cpp_learning_from_demonstration/plots/input_clock.jpg");
    plt::show();

    std::vector <double> x,y;

    for (int i = 0; i <nbStates ; ++i) {
        x.push_back(gmm->returnMu()[i](0));
        y.push_back(gmm->returnMu()[i](1));
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


    delete positionData;
//    delete em_init_kmeans_mlpack;
//    delete gmm, gmr;
//

    return 0;
}
