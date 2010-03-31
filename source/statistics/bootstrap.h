/*
 *  bootstrap.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/30/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */
 
#ifndef _RETSU_STATISTICS_BOOTSTRAP_H_
#define _RETSU_STATISTICS_BOOTSTRAP_H_

#include <source/Common.h>

#include "location.h"
#include "dispersion.h"
#include "shape.h"

namespace Retsu {
  namespace Statistics {
    using namespace std;          

    class Bootstrap {
    public:
      enum Method { BASIC, STUDENTIZED, PERCENTILE, BCA };

    protected:
      Method method;
      double confidence;

    public:
      double std_err;
      double variance;
      pair<double, double> interval;

      Bootstrap(const double& confidence, Method method);
      
      void perform(const vector<double>& values, size_t resamples, double (*stat)(const vector<double>& values));
      
    protected:
      void calculate_stats(const vector<double>& values);
      void calculate_interval(const vector<double>& values);
    };
  }
}

#endif