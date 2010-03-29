/*
 *  conditional.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "conditional.h"

Retsu::Operation::Conditional::Conditional() {
  this->p_conditions = shared_ptr<Conditions>(new Conditions());
}

bool Retsu::Operation::Conditional::has_conditions(Handle<Value> options) {
  return !options->ToObject()->Get(String::New("conditions"))->IsNull();
}

boost::shared_ptr<Retsu::Conditions> Retsu::Operation::Conditional::conditions(Handle<Value> options) {
  if(has_conditions(options)) {
    Local<Value> cond_param = options->ToObject()->Get(String::New("conditions"));
    
    Local<Object> cond_params = cond_param->ToObject();
    Local<Array> cond_columns = cond_params->GetPropertyNames();
    
    for(size_t i = 0; i < cond_columns->Length(); i++) {
      Local<Value> column = cond_columns->Get(Number::New(i));
      Local<Value> cond_val = cond_params->Get(column);
      
      Local<Object> cond_obj = cond_val->ToObject();
      Local<Array> cond_types = cond_obj->GetPropertyNames();
      
      for(size_t k = 0; k < cond_types->Length(); k++) {
        Local<Value> cond_type = cond_types->Get(Number::New(k));
        Local<Value> cond_type_val = cond_obj->Get(cond_type);
        
        string type = *String::AsciiValue(cond_type);
        
        if(cond_type_val->IsNumber()) {
          p_conditions->add(type, *String::AsciiValue(column), cond_type_val->NumberValue());
        } else if(cond_type_val->IsString()) {
          p_conditions->add(type, *String::AsciiValue(column), *String::AsciiValue(cond_type_val));
        } else {
          // it's an array for 'in' get them all out
        }
      }
    }
  }
  
  return p_conditions;
}
