/*
 *  TableOperations.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TableOperations.h"

static Retsu::TableCache table_cache;

v8::Handle<v8::Value> Retsu::TableOperations::create(const v8::Arguments& args) {
  Local<String> key = String::New("name");
  Local<Value> tname_val = args.This()->Get(key);
  string table_name = *String::AsciiValue(tname_val);

  shared_ptr<Table> table = get_cached_table(".", table_name);

  if(table->create()) {
    return Boolean::New(true);
  } else {
    return Boolean::New(false);
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::insert(const v8::Arguments& args) {  
  if(args.Length() < 1) {
    return Boolean::New(false);
  } else {    
    if(!args[0]->IsObject()) {
      return Boolean::New(false);
    } else {
      Local<Object> values = args[0]->ToObject();
      Local<Array> dimensions = values->GetPropertyNames();

      Local<String> key = String::New("name");
      Local<Value> tname_val = args.This()->Get(key);
      string table_name = *String::AsciiValue(tname_val);      
            
      shared_ptr<Table> table = get_cached_table(".", table_name);

      for(size_t i = 0; i < dimensions->Length(); i++) {
        Local<Value> key = dimensions->Get(Number::New(i));
        Local<Value> value = values->Get(key);
        
        if(value->IsNumber()) {
          table->insert(table->next_id(), *String::AsciiValue(key), value->NumberValue());
        } else {
          table->insert(table->next_id(), *String::AsciiValue(key), *String::AsciiValue(value));
        }
      }
      
      return Boolean::New(true);
    }
  }
}

// db.playback.find(1, ['mykey', 'anotherkey']) => 
//   {'mykey' => myvalue, 'anotherkey' => 'anothervalue'}
v8::Handle<v8::Value> Retsu::TableOperations::lookup(const v8::Arguments& args) {  
  if(args.Length() == 0) {
    return Handle<Value>();
  } else if(args.Length() == 1) {
    return lookup_query(args);
  } else if(args.Length() == 2) {
    if(!args[0]->IsNumber()) {
      return Handle<Value>();
    } else {
      if(args[1]->IsString()) {
        return lookup_one(args);
      } else if(args[1]->IsArray()) {
        return lookup_many(args);
      } else {
        return Handle<Value>();
      }
    }
  } else {
    return Handle<Value>();
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_one(const v8::Arguments& args) {
  Local<String> key = String::New("name");
  Local<Value> tname_val = args.This()->Get(key);
  string table_name = *String::AsciiValue(tname_val);      
  
  shared_ptr<Table> table = get_cached_table(".", table_name);
  
  return table->lookup(args[0]->NumberValue(), *String::AsciiValue(args[1]));
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_many(const v8::Arguments& args) {
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_query(const v8::Arguments& args) {
  return Handle<Value>();
}

boost::shared_ptr<Retsu::Table> Retsu::TableOperations::get_cached_table(const string& db_path, const string& table_name) {
  string key = db_path + "/" + table_name;
  TableCache::iterator found = table_cache.find(key);
  
  if(found == table_cache.end()) {
    shared_ptr<Table> table(new Table(db_path, table_name)); 
    table_cache[key] = table;
    return table;
  } else {
    return found->second;
  }
}
