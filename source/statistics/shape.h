/*
 *  shape.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */
 
#ifndef _RETSU_STATISTICS_SHAPE_H_
#define _RETSU_STATISTICS_SHAPE_H_

#include <source/Common.h>

#include "location.h"

namespace Retsu {
  namespace Statistics {
    double variance(const std::vector<double>& values);
    double skewness(const std::vector<double>& values);
    double kurtosis(const std::vector<double>& values);
  }
}

#endif