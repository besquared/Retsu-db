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
  
  Handle<Value> cmd_table(Local<String> name, const AccessorInfo &info) {
    Handle<ObjectTemplate> table_templ = ObjectTemplate::New();
    
    table_templ->Set("name", name);
    table_templ->Set("create", FunctionTemplate::New(Retsu::TableOperations::create));
    table_templ->Set("insert", FunctionTemplate::New(Retsu::TableOperations::insert));
    
    return table_templ->NewInstance();
  }
  
  class Commander {
  public:
    Persistent<Context> context;
    
    Commander();
    ~Commander();
    
    Handle<Value> execute(const string& source);
  };
}

#endif