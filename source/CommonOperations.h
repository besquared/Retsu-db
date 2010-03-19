/*
 *  CommonOperations.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/4/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_COMMON_OPERATIONS_H_
#define _RETSU_COMMON_OPERATIONS_H_

#include "Common.h"

namespace Retsu {  
  namespace CommonOperations {
    using namespace v8;
    using namespace std;
    
    void install(Handle<ObjectTemplate> scope);
    Handle<Value> print(const Arguments& args);
    Handle<Value> inspect(const Arguments& args);
    
    string inspect_object(const Handle<Object> object);
    string inspect_array(const Handle<Array> array);
    string inspect_value(const Handle<Value> value);
  }
}

#endif
