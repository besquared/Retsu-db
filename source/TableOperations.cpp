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

v8::Handle<v8::Value> Retsu::TableOperations::create(const Handle<Value> name) {
  cout << *String::AsciiValue(name) << endl;
  string table_name = *String::AsciiValue(name);
  
  cout << "Creating table " << table_name << endl;

  try {
    Table::create(".", table_name);
    return Boolean::New(true);
  } catch(StorageError e) {
    return Boolean::New(false);
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::create(const v8::Arguments& args) {
  Local<Value> tname_val = args[0]->ToString();
  string table_name = *String::AsciiValue(tname_val);
  
  cout << "Creating table " << table_name << endl;
  
  try {
    Table::create(".", table_name);
    return Boolean::New(true);
  } catch(StorageError e) {
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

v8::Handle<v8::Value> Retsu::TableOperations::each(const v8::Arguments& args) {
  if(!args[0]->IsFunction()) return Handle<Value>();
  Handle<ObjectTemplate> record_templ = ObjectTemplate::New();  
  // table->records->each(&each_func, record_templ, );
  return Handle<Value>();
}

bool Retsu::TableOperations::each_func(RecordID record, Handle<ObjectTemplate> record_templ, Handle<Function> callback) {
  int argc = 1;
  Handle<Value> argv[1];
  Local<Object> record = record_templ->NewInstance();
  record->Set(String::New("id"), Number::New(record));
  
  argv[0] = record;
  Local<Value> result = callback->Call(callback, argc, argv);
  
  if(result->IsTrue()) {
    return true;
  } else {
    return false;
  }
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
