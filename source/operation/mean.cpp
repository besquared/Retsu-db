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
  table(table), column(column), options(options) { 
}

v8::Handle<v8::Value> Retsu::Operation::Mean::perform() {
  map<size_t, Group> groups;
  Handle<Array> results = Array::New();
  Local<Object> params = options->ToObject();
  Local<Value> sample = params->Get(String::New("sample"));

  size_t sample_size;
  if(sample->IsNull()) {
    return ThrowException(String::New("Could not find required key 'sample' in parameters"));
  } else {
    sample_size = sample->NumberValue();
  }

  try {
    Cursor cursor;
    if(conditional.has_conditions(options)) {
      cursor = Cursor(table, sample_size);
    } else {
      cursor = Cursor(table, conditional.conditions(options), sample_size);
    }
    
    grouping.group(cursor, params, groups, results);
    calculate(params, groups, results);
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  } catch(DimensionNotFoundError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return results;
}

// do the actual calculation
v8::Handle<v8::Value> Retsu::Operation::Mean::calculate(
  Local<Object> params, map<size_t, Group>& groups, Handle<Array> results) {
 
  Local<Value> confidence = params->Get(String::New("confidence"));
  Local<Value> bootstrapped = params->Get(String::New("bootstrap"));
  
  double value;
  size_t idx = 0;
  vector<double> values;
  map<string, double> estimate;
  map<size_t, Group>::iterator group;
  for(group = groups.begin(); group != groups.end(); group++, idx++) {
    values.clear();
    table->lookup(column, group->second.records, values, false);
    
    if(bootstrapped->IsUndefined()) {
      // normal it
      // normal(values, estimate);
    } else {
      Statistics::Bootstrap boot(97.5, Statistics::Bootstrap::PERCENTILE);
      boot.perform(values, 1000, &Retsu::Statistics::mean);
    }
    
    results->Get(Number::New(idx))->ToObject()->Set(String::New("value"), Number::New(value));
  }
  
  return Handle<Value>();
}