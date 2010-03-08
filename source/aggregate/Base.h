/*
 *  Base.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_AGGREGATE_BASE_H_
#define _RETSU_AGGREGATE_BASE_H_

#include <Common.h>

namespace Retsu {
  namespace Aggregate {
    using namespace std;
    
    class Base {
    public:
      enum AggregateType { SINGLE, MULTI };

    protected:
      string alias_;
      string measure;
      vector<string> measures;
      AggregateType type;
      
    public:
      Base();
      Base(const string& measure);
      Base(const string& measure, const string& alias);
      Base(const vector<string>& measure, const string& alias);
      
      virtual string alias() = 0;
//      virtual double calculate(Matching& matching) = 0;
//      virtual void apply(vector<WorkSet>& worksets) = 0;
      
      void measure_names(set<string>& results);
    };
	}
}

#endif