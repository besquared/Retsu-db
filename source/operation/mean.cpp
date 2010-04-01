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
    if(!conditional.has_conditions(options)) {
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
 
  Local<Value> confidence_param = params->Get(String::New("confidence"));
  Local<Value> bootstrapped_param = params->Get(String::New("bootstrap"));
  
  double confidence = 97.5;
  if(!confidence_param->IsUndefined()) {
    confidence = confidence_param->NumberValue();
  }
  
  size_t idx = 0;
  vector<double> values;
  map<string, double> estimate;
  map<size_t, Group>::iterator group;
  for(group = groups.begin(); group != groups.end(); group++, idx++) {
    values.clear();
    table->lookup(column, group->second.records, values, false);
    
    Local<Object> result_obj = results->Get(Number::New(idx))->ToObject();
    
    if(bootstrapped_param->IsUndefined()) {
      double mean = Statistics::mean(values);
      double std_err = sqrt(Statistics::variance(values));
      pair<double, double> interval = Statistics::confidence((1 - confidence / 100), mean, std_err, values.size());
      
      result_obj->Set(String::New("value"), Number::New(mean));
      result_obj->Set(String::New("std_err"), Number::New(std_err));
      
      Local<Array> interval_ary = Array::New();
      interval_ary->Set(Number::New(0), Number::New(interval.first));
      interval_ary->Set(Number::New(1), Number::New(interval.second));
      result_obj->Set(String::New("interval"), interval_ary);
    } else {
      size_t replicate = 1000;
      Statistics::Bootstrap::Method interval = Statistics::Bootstrap::NORMAL;
      
      Local<Object> boot_params = bootstrapped_param->ToObject();
      Local<Value> replicate_param = boot_params->Get(String::New("replicate"));
      Local<Value> interval_param = boot_params->Get(String::New("interval"));
      
      if(!replicate_param->IsUndefined()) {
        replicate = replicate_param->NumberValue();
      }
      
      if(!interval_param->IsUndefined()) {
        string interval_str = *String::AsciiValue(interval_param);
        
        if(interval_str == "percentile") {
          interval = Statistics::Bootstrap::PERCENTILE;
        }
      }
      
      Statistics::Bootstrap boot(confidence, interval);
      
      boot.perform(values, replicate, &Retsu::Statistics::mean);
    
      result_obj->Set(String::New("value"), Number::New(boot.mean));
      result_obj->Set(String::New("std_err"), Number::New(boot.std_err));
      
      Local<Array> interval_ary = Array::New();
      interval_ary->Set(Number::New(0), Number::New(boot.interval.first));
      interval_ary->Set(Number::New(1), Number::New(boot.interval.second));
      result_obj->Set(String::New("interval"), interval_ary);
    }
  }
  
  return Handle<Value>();
}