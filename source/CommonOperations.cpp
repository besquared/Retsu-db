/*
 *  CommonOperations.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/4/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "CommonOperations.h"

/*
 * Installation and global commands
 */
void Retsu::CommonOperations::install(Handle<ObjectTemplate> scope) {
  scope->Set(String::New("print"), FunctionTemplate::New(print));
  scope->Set(String::New("inspect"), FunctionTemplate::New(inspect));
}

v8::Handle<v8::Value> Retsu::CommonOperations::print(const Arguments& args) {
  for(size_t i = 0; i < args.Length(); i++) {
    cout << *String::AsciiValue(args[i]->ToString()) << endl;
  }
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::CommonOperations::inspect(const Arguments& args) {
  for(size_t i = 0; i < args.Length(); i++) {
    if(args[i]->IsArray()) {
      cout << inspect_array(Handle<Array>::Cast(args[i])) << endl;
    } else if(args[i]->IsObject()) {
      cout << inspect_object(Handle<Object>::Cast(args[i])) << endl;
    } else {
      cout << inspect_value(args[i]) << endl;
    }
  }
  
  return Handle<Value>();
}

std::string Retsu::CommonOperations::inspect_object(const Handle<Object> object) {
  string result;
  
  result += "{";
  
  Local<Array> keys = object->GetPropertyNames();
  
  for(size_t i = 0; i < keys->Length(); i++) {
    Local<Value> key = keys->Get(Number::New(i));
    Local<Value> value = object->Get(key);
    
    result += string(*String::AsciiValue(key)) + ": ";

    if(value->IsArray()) {
      result += inspect_array(Handle<Array>::Cast(value));
    } else if(value->IsObject()) {
      result += inspect_object(Handle<Object>::Cast(value));
    } else {
      result += inspect_value(value);
    }
    
    if(i < keys->Length() - 1) result += ", ";
  }
  
  result += "}";
  
  return result;
}

std::string Retsu::CommonOperations::inspect_array(const Handle<Array> array) {
  string result;
  
  result += "[";

  for(size_t i = 0; i < array->Length(); i++) {
    Local<Value> value = array->Get(Number::New(i));
    
    if(value->IsArray()) {
      result += inspect_array(Handle<Array>::Cast(value));
    } else if(value->IsObject()) {
      result += inspect_object(Handle<Object>::Cast(value));
    } else {
      result += inspect_value(value);
    }
    
    if(i < array->Length() - 1) result += ", ";    
  }
  
  result += "]";
  
  return result;
}

std::string Retsu::CommonOperations::inspect_value(const Handle<Value> value) {
  string result;
  result += *String::AsciiValue(value);
  return result;
}
