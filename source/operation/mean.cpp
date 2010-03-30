/*
 *  mean.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "mean.h"

Retsu::Operation::Mean::Mean(shared_ptr<Table> table, const string& column, Handle<Value> options) :
  Retsu::Operation::Conditional::Conditional(), table(table), column(column), options(options) { 
}

v8::Handle<v8::Value> Retsu::Operation::Mean::perform() {
  map<size_t, Group> groups;
  Handle<Array> results = Array::New();
  Local<Object> params = options->ToObject();
  
  try {
    Local<Value> sample_param = params->Get(String::New("sample"));

    size_t sample_size;
    if(sample_param->IsNull()) {
      return ThrowException(String::New("Could not find required key 'sample' in parameters"));
    } else {
      sample_size = sample_param->NumberValue();
    }
    
    Cursor cursor;
    if(has_conditions(options)) {
      cursor = Cursor(table, sample_size);
    } else {
      cursor = Cursor(table, conditions(options), sample_size);
    }
    
    group(cursor, params, groups, results);
    
    // do the estimation here, we need to do it once for each group
//    estimate(params, table, groups, results);
    return results;
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  } catch(DimensionNotFoundError e) {
    return ThrowException(String::New(e.what()));
  }
}

// do the actual calculation
v8::Handle<v8::Value> Retsu::Operation::Mean::calculate() {
  // hrmm..
  return Handle<Value>();
}