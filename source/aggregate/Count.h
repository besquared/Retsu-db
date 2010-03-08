/*
 *  Count.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/3/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_AGGREGATE_COUNT_H_
#define _RETSU_AGGREGATE_COUNT_H_

#include "Base.h"

namespace Retsu {
  namespace Aggregate {
    using namespace std;

    class Count : public Aggregate::Base {		
    public:
      Count(const string& measure);
      Count(const string& measure, const string& alias);
      
      virtual string alias();
//      virtual void apply(WorkSet& workset);
//      virtual void apply(vector<WorkSet>& worksets);
    };
	}
}

#endif