/*
 *  bootstrap.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "bootstrap.h"

Retsu::Statistics::Bootstrap::Bootstrap(const double& confidence, Bootstrap::Method method) {
  this->method = method;
  this->confidence = confidence;
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
  
  calculate_stats(stats);
  calculate_interval(stats);
}

void Retsu::Statistics::Bootstrap::calculate_stats(const vector<double>& values) {
  this->variance = Statistics::variance(values);
  this->std_err = sqrt(this->variance);
}

void Retsu::Statistics::Bootstrap::calculate_interval(const vector<double>& values) {
  sort(stats.begin(), stats.end());
}

