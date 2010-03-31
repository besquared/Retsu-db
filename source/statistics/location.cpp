/*
 *  location.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "location.h"

double Retsu::Statistics::mean(const std::vector<double>& values) {
  double sum = 0;
  double count = 0;
  for(size_t i = 0; i < values.size(); i++, count++) {
    sum += values[i];
  }
  return (count > 0 ? sum / count : NAN);
}