/*
 *  Commander.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Commander.h"

Retsu::Commander::Commander() {
  HandleScope handle_scope;

  Handle<ObjectTemplate> global = ObjectTemplate::New();
  
  Retsu::CommonOperations::install(global);
  Retsu::TableOperations::install(global);
  
  context = Context::New(NULL, global);
}

Retsu::Commander::~Commander() {
  context.Dispose();
}

v8::Handle<v8::Value> Retsu::Commander::execute(const string& source) {
  TryCatch try_catch;
  HandleScope handle_scope;
  Context::Scope context_scope(context);

  Handle<String> script = String::New(source.c_str());
  
  Handle<Script> compiled_script = Script::Compile(script);
  if (compiled_script.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    return Boolean::New(false);
  }

  Handle<Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    String::Utf8Value error(try_catch.Exception());
    return Boolean::New(false);
  } else {
    return result;
  }
  return result;
}