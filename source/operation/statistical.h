/*
 *  statistical.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_OPERATION_STATISTICAL_H_
#define _RETSU_OPERATION_STATISTICAL_H_

#include <source/Common.h>

namespace Retsu {
  namespace Operation {
    using namespace std;
    
    class Statistical {
    public:
      
      // These provide estimates of some statistic including
      //  value, variance, stderr and confidence intervals
      void normal(const vector<double>& values, map<string, double>& results);
      void bootstrap(const vector<double>& values, map<string, double>& results);
      void jackknife(const vector<double>& values, map<string, double>& results);
    };
  }
}

#endif