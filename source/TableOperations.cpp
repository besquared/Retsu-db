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
  table_templ->Set(String::New("aggregate"), FunctionTemplate::New(aggregate));
  
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
          Local<Value> key = dimensions->Get(Number::New(i));
          Local<Value> value = values->Get(key);

          if(value->IsNumber()) {
            table->insert(record, *String::AsciiValue(key), value->NumberValue());
          } else {
            table->insert(record, *String::AsciiValue(key), *String::AsciiValue(value));
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
  
  return table->lookup(id->NumberValue(), *String::AsciiValue(name));
}

v8::Handle<v8::Value> Retsu::TableOperations::aggregate(const Arguments& args) {
  if(!args[0]->IsObject()) {
    return ThrowException(String::New("First argument to aggregate must be an object with query parameters"));
  }
  
  Local<Value> table_name = args.This()->Get(String::New("name"));
      
  map<size_t, Group> groups;
  Local<Array> results = Array::New();
  Local<Object> params = Local<Object>::Cast(args[0]);
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));

  try {
    Handle<Value> grouped = group(params, table, groups, results);
    if(!grouped->IsTrue()) return grouped;
    
    Handle<Value> aggregated = aggregate(params, table, groups, results);
    return aggregated;
    
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  } catch(DimensionNotFoundError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return Handle<Value>();  
}

v8::Handle<v8::Value> Retsu::TableOperations::group(Local<Object> params, const shared_ptr<Table> table, 
                                                    map<size_t, Group>& groups, Local<Array> results) {
  
  Local<Value> group_param = params->Get(String::New("group"));
  
  if(group_param->IsNull()) {
    return ThrowException(String::New("Could not find key 'group' in aggregate parameters"));
  }
  
  Local<Array> group_columns = Local<Array>::Cast(group_param);
  
  vector<string> group_by;
  for(size_t k = 0; k < group_columns->Length(); k++) {
    group_by.push_back(*String::AsciiValue(group_columns->Get(Number::New(k))));
  }  
  
  size_t hash_key;
  uint64_t record_id;
  string value;
  vector<string> values;
  table->cursor_init();
  while((record_id = table->cursor_next()) > 0) {
    values.clear();
    for(size_t i = 0; i < group_by.size(); i++) {
      table->lookup(record_id, group_by[i], value);
      values.push_back(value);
    }
    
    hash_key = boost::hash_range(values.begin(), values.end());      
    
    // lookup the key in the map
    map<size_t, Group>::iterator found = groups.find(hash_key);
    
    if(found == groups.end()) {
      Group group(table);
      
      group.records.push_back(record_id);
      for(size_t j = 0; j < group_by.size(); j++) {
        group.values[group_by[j]] = values[j];
      }
      
      groups[hash_key] = group;
      results->Set(Number::New(results->Length()), Object::New());
    } else {
      found->second.records.push_back(record_id);
    }
  }
  
  return Boolean::New(true);
}

/*
 * Aggregates groups based on query options
 */

v8::Handle<v8::Value> Retsu::TableOperations::aggregate(Local<Object> params, const shared_ptr<Table> table, 
                                                    map<size_t, Group>& groups, Local<Array> results) {
  
  Local<Value> aggregate = params->Get(String::New("aggregates"));
  
  if(aggregate->IsNull()) {
    return ThrowException(String::New("Could not find key 'aggregate' in aggregate parameters"));
  }
  
  Local<Object> agg_params = Local<Object>::Cast(aggregate);
  Local<Array> agg_names = agg_params->GetPropertyNames();
  
  for(size_t i = 0; i < agg_names->Length(); i++) {
    Local<Value> agg_name = agg_names->Get(Number::New(i));
    Local<Value> agg_def = agg_params->Get(agg_name);
    
    double value;
    size_t idx = 0;
    map<size_t, Group>::iterator group;
    
    if(agg_def->IsFunction()) {
      // do the group function thing
    } else if(agg_def->IsObject()) {
      Local<Object> agg_obj = Local<Object>::Cast(agg_def);
      
      if(agg_obj->Has(String::New("count"))) {
        for(group = groups.begin(); group != groups.end(); group++, idx++) {
          value = group->second.count();
          Local<Object>::Cast(results->Get(Number::New(idx)))->Set(agg_name, Number::New(value));            
        } 
      } else if(agg_obj->Has(String::New("sum"))) {
        Local<Value> column = agg_obj->Get(String::New("sum"));
        for(group = groups.begin(); group != groups.end(); group++, idx++) {
          value = group->second.sum(*String::AsciiValue(column));
          Local<Object>::Cast(results->Get(Number::New(idx)))->Set(agg_name, Number::New(value));            
        }
      } else if(agg_obj->Has(String::New("average"))) {
        Local<Value> column = agg_obj->Get(String::New("average"));
        for(group = groups.begin(); group != groups.end(); group++, idx++) {
          value = group->second.average(*String::AsciiValue(column));
          Local<Object>::Cast(results->Get(Number::New(idx)))->Set(agg_name, Number::New(value));            
        }
      }
    }
  }
  
  return results;  
}