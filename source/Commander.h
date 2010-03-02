/*
 *  Commander.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_COMMANDER_H_
#define _RETSU_COMMANDER_H_

#include "Common.h"
#include "TableOperations.h"

namespace Retsu {
  using namespace v8;
  using namespace std;
  
  class Commander {
  public:
    Persistent<Context> context;
    
    Commander();
    ~Commander();
    
    Handle<Value> execute(const string& source);
  };
  
  Handle<Value> cmd_table(Local<String> name, const AccessorInfo &info);
}

#endif