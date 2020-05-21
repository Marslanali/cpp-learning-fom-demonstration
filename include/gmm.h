//
// Created by arslan on 16/11/19.
//

#ifndef PROGRAMMING_BY_DEMONSTRATION_GMM_H
#define PROGRAMMING_BY_DEMONSTRATION_GMM_H

#include <armadillo>
#include <vector>
#include "../include/mvn.h"

class GMM {
 private:
  const float diag_reg_fact = 1e-4f;

  uint nb_vars;
  uint nb_states;
  uint nb_data_points;

  arma::Mat<double> data;
  std::vector<arma::Col<double>> mu;
  std::vector<arma::Mat<double>> sigma;
  arma::Col<double> priors;

  std::vector<GaussianDistribution> pdf_vec;
  GaussianDistribution pdf;

 public:
  void EM(const arma::Mat<double>& _data, const arma::Col<double>& _priors, const std::vector<arma::Col<double>>& _mu,
          const std::vector<arma::Mat<double>>& _sigma);
  arma::Col<double> return_priors();
  std::vector<arma::Col<double>> return_mu();
  std::vector<arma::Mat<double>> return_sigma();
};

#endif  // PROGRAMMING_BY_DEMONSTRATION_GMM_H
