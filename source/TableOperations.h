/*
 *  TableOperations.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _TABLE_OPERATIONS_H
#define _TABLE_OPERATIONS_H

#include "Common.h"

namespace Retsu {
  namespace TableOperations {
    using namespace v8;
    using namespace std;
    
    Handle<Value> insert(const Arguments& args) {
      Local<String> key = String::New("name");
      Local<Value> tname_val = args.This()->Get(key);
      string table_name = *String::AsciiValue(tname_val);

      Retsu::Table table(".", table_name);

      if(args.Length() < 1) {
        return Boolean::New(false);
      } else {
        if(!args[0]->IsObject()) {
          return Boolean::New(false);
        } else {
          Local<Object> values = args[0]->ToObject();
          Local<Array> dimensions = values->GetPropertyNames();
          
          for(size_t i = 0; i < dimensions->Length(); i++) {
            Local<Number> index = Number::New(i);
            Local<Value> key = dimensions->Get(index);
            Local<Value> value = values->Get(key);
            
            if(value->IsNumber()) {
              table.insert(table.next_id(), *String::AsciiValue(key), value->NumberValue());
            } else {
              table.insert(table.next_id(), *String::AsciiValue(key), *String::AsciiValue(value));
            }
          }
          
          return Boolean::New(true);
        }
      }      
    }
  }
}

#endif
