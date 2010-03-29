/*
 *  conditional.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_OPERATION_CONDITIONAL_H_
#define _RETSU_OPERATION_CONDITIONAL_H_

#include <source/Common.h>
#include <source/Conditions.h>

namespace Retsu {
  namespace Operation {
    using namespace v8;
    using namespace std;
    
    class Conditional {
    protected:
      shared_ptr<Conditions> p_conditions;
    
    public:
      Conditional();
      
      bool has_conditions(Handle<Value> options);
      shared_ptr<Conditions> conditions(Handle<Value> options);
    };
  }
}

#endif