/*
 *  confidence.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/31/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_STATISTICS_CONFIDENCE_H_
#define _RETSU_STATISTICS_CONFIDENCE_H_

#include <source/Common.h>

#include "location.h"
#include "shape.h"

namespace Retsu {
  namespace Statistics {
    std::pair<double, double> confidence(const std::vector<double>& values, double alpha);
    std::pair<double, double> confidence(double alpha, double mean, double std_err, double sample_size);
  }
}

#endif