/*
 *  Aggregator.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/7/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_AGGREGATOR_H_
#define _RETSU_AGGREGATOR_H_

#include "Common.h"
#include "Conditions.h"
#include "Aggregates.h"

namespace Retsu {
  using namespace v8;
  using namespace std;
  
  class Aggregator {
  public:
    Conditions* conditions;
    Aggregates* aggregates;
    vector<string> group_by;
    
    Aggregator();
    ~Aggregator();
  };
}

#endif