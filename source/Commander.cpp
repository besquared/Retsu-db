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

  Handle<ObjectTemplate> db = ObjectTemplate::New();
  db->SetNamedPropertyHandler(cmd_table);

  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::New("db"), db);
  
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
}

v8::Handle<v8::Value> Retsu::cmd_table(v8::Local<v8::String> name, const v8::AccessorInfo &info) {
  Handle<ObjectTemplate> table_templ = ObjectTemplate::New();
  
  table_templ->Set("name", name);
  table_templ->Set("create", FunctionTemplate::New(Retsu::TableOperations::create));
  table_templ->Set("insert", FunctionTemplate::New(Retsu::TableOperations::insert));
  
  return table_templ->NewInstance();
}