/*
 *  grouping.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "grouping.h"

v8::Handle<v8::Value> Retsu::Operation::Grouping::group(
  Cursor& cursor, Local<Object> params, map<size_t, Group>& groups, Handle<Array> results) {
  
  Local<Value> group_param = params->Get(String::New("group"));
  
  if(group_param->IsNull()) {
    return ThrowException(String::New("Could not find key 'group' in parameters"));
  }
  
  Local<Array> group_columns = Local<Array>::Cast(group_param);
  
  vector<string> group_by;
  for(size_t k = 0; k < group_columns->Length(); k++) {
    group_by.push_back(*String::AsciiValue(group_columns->Get(Number::New(k))));
  }

    
  size_t hash_key;
  string value;
  vector<string> values;
  while(cursor.next()) {
    values.clear();
    vector<string>::iterator groupcol;
    for(groupcol = group_by.begin(); groupcol != group_by.end(); groupcol++) {
      cursor.lookup(*groupcol, value);
      values.push_back(value);
    }
    
    hash_key = boost::hash_range(values.begin(), values.end());      
    
    // lookup the key in the map
    map<size_t, Group>::iterator found = groups.find(hash_key);
    
    if(found == groups.end()) {
      Group group = groups[hash_key];
      
      group.records.push_back(cursor.current);
      for(size_t j = 0; j < group_by.size(); j++) {
        group.values[group_by[j]] = values[j];
      }
      
      Local<Value> idx_key = Number::New(results->Length());
      
      results->Set(idx_key, Object::New());
      for(size_t j = 0; j < group_by.size(); j++) {
        results->Get(idx_key)->ToObject()->Set(String::New(group_by[j].c_str()), String::New(values[j].c_str()));
      }
    } else {
      found->second.records.push_back(cursor.current);
    }
  }
  
  return Boolean::New(true);
}
