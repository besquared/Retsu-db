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
      
      RecordID record = table->next_id();
      for(size_t i = 0; i < dimensions->Length(); i++) {
        Local<Value> key = dimensions->Get(Number::New(i));
        Local<Value> value = values->Get(key);

        if(value->IsNumber()) {
          table->insert(record, *String::AsciiValue(key), value->NumberValue());
        } else {
//          cout << "Inserting " << record << ": " << *String::AsciiValue(key) << " => " << *String::AsciiValue(value) << endl;
          table->insert(record, *String::AsciiValue(key), *String::AsciiValue(value));
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


// 
v8::Handle<v8::Value> Retsu::TableOperations::aggregate(const Arguments& args) {
  cout << "inside aggregate" << endl;
  
  if(!args[0]->IsObject()) {
    return ThrowException(String::New("Argument must be an object"));
  }

  Local<Object> params = Local<Object>::Cast(args[0]);
  Local<Value> table_name = args.This()->Get(String::New("name"));
  Local<Value> grouping_dims = params->Get(String::New("group"));
  
  if(grouping_dims->IsNull()) {
    return ThrowException(String::New("Could not find key 'group' in aggregate parameters"));
  }
  
  Local<Array> group_ary = Local<Array>::Cast(grouping_dims);
  
  vector<string> group_by;
  for(size_t k = 0; k < group_ary->Length(); k++) {
    group_by.push_back(*String::AsciiValue(group_ary->Get(Number::New(k))));
  }
  
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));
  
  try {
    string value;
    size_t hash_key;
    uint64_t current;
    vector<string> group_vals;
    map<size_t, Group> groups;
    
    table->cursor_init();
    while((current = table->cursor_next()) > 0) {
      group_vals.clear();
      for(size_t i = 0; i < group_by.size(); i++) {
        table->lookup(current, group_by[i], value);
        group_vals.push_back(value);
      }
      
      hash_key = boost::hash_range(group_vals.begin(), group_vals.end());      
      
      // lookup the key in the map
      map<size_t, Group>::iterator found = groups.find(hash_key);
      
      if(found == groups.end()) {
        Group group;
        
        group.records.push_back(current);
        for(size_t j = 0; j < group_by.size(); j++) {
          group.values[group_by[j]] = group_vals[j];
        }
        
        groups[hash_key] = group;
      } else {
        found->second.records.push_back(current);
      }
    }
    
    cout << groups.size() << endl;
  } catch(StorageError e) {
    return ThrowException(String::New(e.what()));
  } catch(DimensionNotFoundError e) {
    return ThrowException(String::New(e.what()));
  }
  
  return Handle<Value>();  
}

v8::Handle<v8::Value> Retsu::TableOperations::aggregate_groups(const Arguments& args) {
}

v8::Handle<v8::Value> Retsu::TableOperations::group(const Arguments& args) {
  // so we're gonna like hella group here and stuff, scan and then construct
  vector<string> group_by;
  for(size_t i = 0; i < args.Length() - 1; i++) {
    group_by.push_back(*String::AsciiValue(args[i]));
  }
  
  Local<String> key = String::New("name");
  Local<Value> table_name = args.This()->Get(key);
  shared_ptr<Table> table = TableManager::instance().get(*String::AsciiValue(table_name));
  
  // lets just do the grouping straight up right here
  //  first lets run filter() to get a list of record id's that matter
  //  then lets go through and group of all of them then return this group
  
  return Handle<Value>();
}

v8::Handle<v8::Value> Retsu::TableOperations::construct(vector<string>& dimensions, RIDTree& lookedup, size_t offset, map<string, string>& values, RIDList& records) {
//	if(inquired_dims.size() == offset) {
//		RIDList intersected = records & instantiated;
//		
//		if(intersected.size() > 0) {
//      map<string, string> group_values;
//      group_values.insert(values.begin(), values.end());
//      group_values.insert(instantiate.begin(), instantiate.end());
//      worksets.push_back(WorkSet(group_values, intersected));
//		}
//    
//		return;
//	}
//	
//  string& dimension = inquired_dims[offset];
//  
//  RIDMap::iterator rpair;
//	RIDMap rmap = inquired[dimension];
//	for(rpair = rmap.begin(); rpair != rmap.end(); rpair++) {
//		RIDList intersection = 
//		(records.empty() ? rpair->second : records & rpair->second);
//		
//		if(intersection.size() > 0) {
//      values[dimension] = rpair->first;
//			Construct(instantiate, instantiated, inquired_dims, 
//								inquired, offset + 1, values, intersection, worksets);
//      values.erase(dimension);
//		}
//	}
  return Handle<Value>();
}