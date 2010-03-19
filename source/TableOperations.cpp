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
          Local<Value> column = dimensions->Get(Number::New(i));
          Local<Value> value = values->Get(key);

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
    
    return results;
    
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  } catch(DimensionNotFoundError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return Handle<Value>();  
}

// Sometimes we have conditions
v8::Handle<v8::Value> Retsu::TableOperations::condition(Local<Object> params, shared_ptr<Conditions> conditions) {
  Local<Value> cond_param = params->Get(String::New("conditions"));
    
  if(cond_param->IsNull()) {
    return Boolean::New(false);
  } else {
    Local<Object> cond_params = Local<Object>::Cast(cond_param);
    Local<Array> cond_columns = cond_params->GetPropertyNames();
    
    for(size_t i = 0; i < cond_columns->Length(); i++) {
      Local<Value> column = cond_columns->Get(Number::New(i));
      Local<Value> cond_val = cond_params->Get(column);
      Local<Object> cond_obj = Local<Object>::Cast(cond_val);
      Local<Array> cond_types = cond_obj->GetPropertyNames();

      for(size_t k = 0; k < cond_types->Length(); k++) {
        Local<Value> cond_type = cond_types->Get(Number::New(k));
        Local<Value> cond_type_val = cond_obj->Get(cond_type);
        
        string type = *String::AsciiValue(cond_type);
        string value = *String::AsciiValue(cond_type_val);
        
        if(type == "eq") {
          conditions->eq(*String::AsciiValue(column), value);
        } else if(type == "neq") {
          conditions->neq(*String::AsciiValue(column), value);
        } else if(type == "gt") {
          conditions->gt(*String::AsciiValue(column), value);
        } else if(type == "gte") {
          conditions->gte(*String::AsciiValue(column), value);
        } else if(type == "lt") {
          conditions->lt(*String::AsciiValue(column), value);
        } else if(type == "lte") {
          conditions->lte(*String::AsciiValue(column), value); 
        } else if(type == "in") {
          // do some in stuff here, unwrap the array and whatnot
        }
      }
    }
    
    return Boolean::New(true);
  }
}

// Iterate over the table with a cursor and group rows
v8::Handle<v8::Value> Retsu::TableOperations::group(Local<Object> params, const shared_ptr<Table> table, 
                                                    map<size_t, Group>& groups, Local<Array> results) {
    
  Local<Value> group_param = params->Get(String::New("group"));
  Local<Value> sample_size_param = params->Get(String::New("sample_size"));

  if(group_param->IsNull()) {
    return ThrowException(String::New("Could not find key 'group' in aggregate parameters"));
  }
  
  Local<Array> group_columns = Local<Array>::Cast(group_param);
  
  vector<string> group_by;
  for(size_t k = 0; k < group_columns->Length(); k++) {
    group_by.push_back(*String::AsciiValue(group_columns->Get(Number::New(k))));
  }  
  
  shared_ptr<Conditions> conditions(new Conditions());
  Handle<Value> conditioned = condition(params, conditions);
    
  size_t sample_size;
  if(sample_size_param->IsNull()) {
    sample_size = 0;
  } else {
    sample_size = sample_size_param->NumberValue();
  }
  
  Cursor cursor;
  size_t hash_key;
  uint64_t record_id;
  string value;
  vector<string> values;
  
  if(conditions->empty()) {
    cursor = (sample_size == 0 ? Cursor(table) : Cursor(table, sample_size));    
  } else {
    cursor = (sample_size == 0 ? Cursor(table, conditions) : Cursor(table, conditions, sample_size));    
  }
  
  while((record_id = cursor.next()) > 0) {
    values.clear();
    for(size_t i = 0; i < group_by.size(); i++) {
      table->lookup(group_by[i], record_id, value);
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
      
      Local<Value> idx_key = Number::New(results->Length());
      
      results->Set(idx_key, Object::New());
      for(size_t j = 0; j < group_by.size(); j++) {
        Local<Object>::Cast(results->Get(idx_key))->Set(String::New(group_by[j].c_str()), String::New(values[j].c_str()));
      }      
    } else {
      found->second.records.push_back(record_id);
    }
  }
  
  return Boolean::New(true);
}

v8::Handle<v8::Value> Retsu::TableOperations::aggregate(Local<Object> params, const shared_ptr<Table> table, 
                                                    map<size_t, Group>& groups, Local<Array> results) {
  
  if(groups.size() == 0) { return Boolean::New(false); }
  
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
  
  return Boolean::New(true);
}