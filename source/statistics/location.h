/*
 *  location.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_STATISTICS_LOCATION_H_
#define _RETSU_STATISTICS_LOCATION_H_

#include <source/Common.h>

namespace Retsu {
  namespace Statistics {
    double mean(const std::vector<double>& values);
    double gmean(const std::vector<double>& values);
    double hmean(const std::vector<double>& values);
    double tmean(const std::vector<double>& values);
    double median(const std::vector<double>& values);
    double mode(const std::vector<double>& values);
  }
}

#endif