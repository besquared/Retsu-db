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
  scope->Set(String::New("drop_table"), FunctionTemplate::New(drop));
  
  // create
  // insert
  // aggregate
  
}

v8::Handle<v8::Value> Retsu::TableOperations::get_table_proxy(Local<String> name, const AccessorInfo& info) {  
  table_templ = ObjectTemplate::New();
  table_templ->Set(String::New("insert"), FunctionTemplate::New(insert));
  table_templ->Set(String::New("lookup"), FunctionTemplate::New(lookup));
  table_templ->Set(String::New("each"), FunctionTemplate::New(each)); 
  table_templ->Set(String::New("mean"), FunctionTemplate::New(mean));

  Local<Object> table_proxy = table_templ->NewInstance();
  table_proxy->Set(String::New("name"), name);
  
  return table_proxy;
}

v8::Handle<v8::Value> Retsu::TableOperations::create(const Arguments& args) {
  Local<Value> tname_val = args[0]->ToString();
  string table_name = *String::AsciiValue(tname_val);
  
  try {
    Table::create(".", table_name);
    return Boolean::New(true);
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::drop(const Arguments& args) {
  Local<Value> tname_val = args[0]->ToString();
  string table_name = *String::AsciiValue(tname_val);
  
  try {
    TableManager::instance().drop(table_name);
    return Boolean::New(true);
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  }
}

v8::Handle<v8::Value> Retsu::TableOperations::insert(const Arguments& args) {  
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
            
      shared_ptr<Table> table = TableManager::instance().get(table_name);
      
      try {
        RecordID record = table->next_id();
        for(size_t i = 0; i < dimensions->Length(); i++) {
          Local<Value> column = dimensions->Get(Number::New(i));
          Local<Value> value = values->Get(column);

          if(value->IsNumber()) {
            table->insert(*String::AsciiValue(column), record, value->NumberValue());
          } else {
            table->insert(*String::AsciiValue(column), record, *String::AsciiValue(value));
          }
        }
      } catch(StorageError e) {
        cout << e.what() << endl;
        return ThrowException(String::New(e.what()));
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
  shared_ptr<Table> table = TableManager::instance().get(table_name);
  
  // do we want a string or a number here?
  string result;
  table->lookup(*String::AsciiValue(args[1]), args[0]->NumberValue(), result);
  return String::New(result.c_str());
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_many(const Arguments& args) {
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::lookup_query(const Arguments& args) {
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::each(const Arguments& args) {
  if(!args[0]->IsFunction()) {
    return ThrowException(String::New("Each which takes a single function argment"));
  }
  
  Local<String> key = String::New("name");
  Local<Value> table_name = args.This()->Get(key);
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));
  
  Local<Function> callback = Local<Function>::Cast(args[0]);

  try {
    Handle<Value> argv[1];

    record_templ = ObjectTemplate::New();
    record_templ->Set(String::New("table"), table_name);
    record_templ->SetNamedPropertyHandler(get_record_data);
    Local<Object> record = record_templ->NewInstance();
    
    uint64_t current;
    table->cursor_init();
    while((current = table->cursor_next()) > 0) {
      record->Set(String::New("id"), Number::New(current));
      argv[0] = record;

      callback->Call(callback, 1, argv);
    }
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::get_record_data(Local<String> name, const AccessorInfo& info) {
  Local<Object> record = info.This();
  Local<Value> id = record->GetRealNamedProperty(String::New("id"));
  
  if(name->Equals(String::New("id"))) return id;
  
  Local<Value> table_name = record->GetRealNamedProperty(String::New("table"));
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));
  
  string result;
  table->lookup(*String::AsciiValue(name), id->NumberValue(), result);
  return String::New(result.c_str());
}

/*
 * Grouping & Aggregation
 */
 
v8::Handle<v8::Value> Retsu::TableOperations::mean(const Arguments& args) {  
  if(!args[0]->IsString()) {
    return ThrowException(String::New("First argument to mean must be a string"));
  }
  
  Local<Value> table_name = args.This()->Get(String::New("name"));
  
  string column = *String::AsciiValue(args[0]);
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));

  return Retsu::Operation::Mean(table, column, args[1]).perform();
}