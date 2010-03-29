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

#include "grouping.h"
#include "conditional.h"
#include "statistical.h"

namespace Retsu {
  namespace Operation {
    using namespace std;
    using namespace v8;
    using namespace boost;
    
    class Mean : public Grouping, public Conditional, public Statistical {
    protected:
      string column;
      shared_ptr<Table> table;
      Handle<Value> options;
    
    public:
      Mean(shared_ptr<Table> table, const string& column, Handle<Value> options);
      
      Handle<Value> perform();
    };
  }
}

#endif