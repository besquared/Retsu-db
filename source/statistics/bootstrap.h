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
#include "confidence.h"

namespace Retsu {
  namespace Statistics {
    using namespace std;          

    class Bootstrap {
    public:
      enum Method { NORMAL, PERCENTILE, BCA };

    protected:
      Method method;
      double confidence;

    public:
      double mean;
      double std_err;
      double variance;
      pair<double, double> interval;

      Bootstrap(const double& confidence, Method method);
      
      void perform(const vector<double>& values, size_t resamples, double (*stat)(const vector<double>& values));
      
    protected:
      void calculate_stats(const vector<double>& values);
      void calculate_interval(const vector<double>& values);
      void calculate_normal_interval(const vector<double>& values);
      void calculate_percentile_interval(const vector<double>& values);
      void calculate_bias_corrected_interval(const vector<double>& values);
    };
  }
}

#endif