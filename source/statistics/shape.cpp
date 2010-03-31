/*
 *  shape.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "shape.h"

// Sample variance
double Retsu::Statistics::variance(const std::vector<double>& values) {
  double sum = 0;
  double x_bar = mean(values);
  std::vector<double>::const_iterator value;
  for(value = values.begin(); value != values.end(); value++) {
    sum += (*value - x_bar) * (*value - x_bar);
  }
  return sum / (values.size() - 1);
}

double Retsu::Statistics::skewness(const std::vector<double>& values) {
  return 0.0;
}

double Retsu::Statistics::kurtosis(const std::vector<double>& values) {
  return 0.0;
}
