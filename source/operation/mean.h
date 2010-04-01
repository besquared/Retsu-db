/*
 *  mean.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_OPERATION_MEAN_H_
#define _RETSU_OPERATION_MEAN_H_

#include <source/Common.h>
#include <source/Table.h>
#include <source/Group.h>
#include <source/Cursor.h>

#include <source/statistics/location.h>
#include <source/statistics/bootstrap.h>
#include <source/statistics/confidence.h>

#include "grouping.h"
#include "conditional.h"

namespace Retsu {
  namespace Operation {
    using namespace std;
    using namespace v8;
    using namespace boost;
    
    class Mean {
    protected:
      string column;
      shared_ptr<Table> table;
      Handle<Value> options;
      
      // Mixin-like composition
      Grouping grouping;
      Conditional conditional;
      
    public:
      Mean(shared_ptr<Table> table, const string& column, Handle<Value> options);
      
      Handle<Value> perform();
        
    protected:
      Handle<Value> calculate(Local<Object> params, map<size_t, Group>& groups, Handle<Array> results);
      double calculate(const vector<double>& values);
    };
  }
}

#endif