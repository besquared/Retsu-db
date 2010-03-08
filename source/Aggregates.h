/*
 *  Aggregates.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/21/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_AGGREGATES_H_
#define _RETSU_AGGREGATES_H_

#include "Common.h"
#include "aggregate/Sum.h"
#include "aggregate/Count.h"

namespace Retsu {
  using namespace std;
  using namespace boost;

  class Aggregates {
  protected:
    vector< shared_ptr<Aggregate::Base> > aggregates;

  public:      
    void sum(const string& name);
    void count(const string& name);
    
    set<string> aliases();
    void measure_names(set<string>& results);
  };
}

#endif