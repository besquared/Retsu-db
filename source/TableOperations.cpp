/*
 *  TableOperations.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TableOperations.h"

/*
 * Caches
 */

static Retsu::TableCache table_cache;

/*
 * Objects & Proxies
 */
static v8::Handle<v8::ObjectTemplate> table_templ;
static v8::Handle<v8::ObjectTemplate> record_templ;

/*
 * Installation and global commands
 */
void Retsu::TableOperations::install(Handle<ObjectTemplate> scope) {  
  // Do the installation
  Local<ObjectTemplate> tables_proxy = ObjectTemplate::New();
  tables_proxy->SetNamedPropertyHandler(get_table_proxy);
  scope->Set(String::New("tables"), tables_proxy);
  scope->Set(String::New("create_table"), FunctionTemplate::New(create));
}

v8::Handle<v8::Value> Retsu::TableOperations::get_table_proxy(Local<String> name, const AccessorInfo& info) {  
  table_templ = ObjectTemplate::New();
  table_templ->Set(String::New("insert"), FunctionTemplate::New(insert));
  table_templ->Set(String::New("lookup"), FunctionTemplate::New(lookup));
  table_templ->Set(String::New("each"), FunctionTemplate::New(each));   
  
  Local<Object> table_proxy = table_templ->NewInstance();
  table_proxy->Set(String::New("name"), name);
  
  return table_proxy;
}

v8::Handle<v8::Value> Retsu::TableOperations::create(const Handle<Value> name) {
  cout << *String::AsciiValue(name) << endl;
  string table_name = *String::AsciiValue(name);
  
  cout << "Creating table " << table_name << endl;

  try {
    Table::create(".", table_name);
    return Boolean::New(true);
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::create(const Arguments& args) {
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

v8::Handle<v8::Value> Retsu::TableOperations::insert(const Arguments& args) {  
  cout << "Inserting record" << endl;
  
  if(args.Length() < 1) {
    return ThrowException(String::New("Invalid arguments to tables.insert"));
  } else {    
    if(!args[0]->IsObject()) {
      return ThrowException(String::New("Invalid arguments to tables.insert"));
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
v8::Handle<v8::Value> Retsu::TableOperations::lookup(const Arguments& args) {  
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

v8::Handle<v8::Value> Retsu::TableOperations::lookup_one(const Arguments& args) {
  Local<String> key = String::New("name");
  Local<Value> tname_val = args.This()->Get(key);
  string table_name = *String::AsciiValue(tname_val);      
  
  shared_ptr<Table> table = get_cached_table(".", table_name);
  
  return table->lookup(args[0]->NumberValue(), *String::AsciiValue(args[1]));
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_many(const Arguments& args) {
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_query(const Arguments& args) {
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::each(const Arguments& args) {
  if(!args[0]->IsFunction()) {
    return ThrowException(String::New("Invalid arguments to each which takes a single function argment"));
  }
  
  Local<String> key = String::New("name");
  Local<Value> tname_val = args.This()->Get(key);
  string table_name = *String::AsciiValue(tname_val);      
  
  cout << "Eaching through table " << table_name << endl;

  shared_ptr<Table> table = get_cached_table(".", table_name);
  
  try {
    record_templ = ObjectTemplate::New();
    record_templ->SetNamedPropertyHandler(get_record_data);
    record_templ->Set(String::New("table"), String::New(table_name.c_str()));

    table->each(&each_callback, record_templ, Handle<Function>::Cast(args[0]));
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return Handle<Value>();
}

void Retsu::TableOperations::each_callback(RecordID id, Handle<ObjectTemplate> record_templ, Handle<Function> callback) {    
  Handle<Value> argv[1];
  
  Local<Object> record = record_templ->NewInstance();
  record->Set(String::New("id"), Number::New(id));
  
  argv[0] = record;
  callback->Call(callback, 1, argv);
}

v8::Handle<v8::Value> Retsu::TableOperations::get_record_data(Local<String> name, const AccessorInfo& info) {
  Local<Object> record = info.This();
  Local<Value> id = record->GetRealNamedProperty(String::New("id"));
  Local<Value> table_name = record->GetRealNamedProperty(String::New("table"));
  shared_ptr<Table> table = get_cached_table(".", *String::AsciiValue(table_name));
  
  return table->lookup(id->NumberValue(), *String::AsciiValue(name));
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
