/*
 *  confidence.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/31/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "confidence.h"

std::pair<double, double> Retsu::Statistics::confidence(const std::vector<double>& values, double alpha) {
  double mean = Statistics::mean(values);
  double std_err = sqrt(Statistics::variance(values));
  return confidence(alpha, mean, std_err, values.size());
}

std::pair<double, double> Retsu::Statistics::confidence(double alpha, double mean, double std_err, double sample_size) {
  std::pair<double, double> interval;

  boost::math::students_t dist(sample_size - 1);
  double t = boost::math::quantile(complement(dist, alpha / 2));
  
  double width = t * std_err / sqrt(sample_size);
  interval.first = mean - width;
  interval.second = mean + width;
  
  return interval;
}