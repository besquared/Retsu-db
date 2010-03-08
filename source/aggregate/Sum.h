/*
 *  Sum.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/2/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_AGGREGATE_SUM_H_
#define _RETSU_AGGREGATE_SUM_H_

#include "Base.h"

namespace Retsu {
  namespace Aggregate {
    using namespace std;

    class Sum : public Aggregate::Base {		
    public:
      Sum(const string& measure);
      Sum(const string& measure, const string& alias);

      virtual string alias();
//      virtual void apply(WorkSet& group);
//      virtual void apply(vector<WorkSet>& worksets);	
//      virtual double calculate(Matching& matching);
    };
	}
}

#endif