/*
 *  bootstrap.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "bootstrap.h"

Retsu::Statistics::Bootstrap::Bootstrap(const double& confidence, Bootstrap::Method method) :
  method(method), confidence(confidence) {
}

void Retsu::Statistics::Bootstrap::perform(const vector<double>& values, size_t resamples, double (*stat)(const vector<double>& values)) {
  vector<double> stats;
  vector<double> resample;
  for(size_t i = 0; i < resamples; i++) {
    resample.clear();
    size_t values_size = values.size();
    for(size_t k = 0; k < values_size; k++) {
      resample.push_back(values[rand() % values_size]);
    }
    stats.push_back((*stat)(resample));
  }
  
  sort(stats.begin(), stats.end());
  
  calculate_stats(stats);
  calculate_interval(stats);
}

void Retsu::Statistics::Bootstrap::calculate_stats(const vector<double>& values) {
  mean = Statistics::mean(values);
  variance = Statistics::variance(values);
  std_err = sqrt(this->variance);
}

void Retsu::Statistics::Bootstrap::calculate_interval(const vector<double>& values) {
  switch(method) {
    case Bootstrap::NORMAL:
      calculate_normal_interval(values);
    case Bootstrap::PERCENTILE:
      calculate_percentile_interval(values);
    case Bootstrap::BCA:
      break;
  }
}

void Retsu::Statistics::Bootstrap::calculate_normal_interval(const vector<double>& values) {
  interval = Statistics::confidence((1 - confidence / 100), mean, std_err, values.size());
}

void Retsu::Statistics::Bootstrap::calculate_percentile_interval(const vector<double>& values) {
  size_t lower = (values.size() * (1 - confidence)) / 2;
  size_t upper = values.size() - lower - 1;

  interval.first = values[lower];
  interval.second = values[upper];
}

void Retsu::Statistics::Bootstrap::calculate_bias_corrected_interval(const vector<double>& values) {
  // TODO IMPLEMENT THIS
}
