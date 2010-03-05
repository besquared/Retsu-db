/*
 *  TableOperations.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_TABLE_OPERATIONS_H_
#define _RETSU_TABLE_OPERATIONS_H_

#include "Common.h"
#include "Table.h"

namespace Retsu {  
  typedef std::map< std::string, boost::shared_ptr<Table> > TableCache;

  namespace TableOperations {
    using namespace v8;
    using namespace std;
    using namespace boost;

    void install(Handle<ObjectTemplate> scope);
    Handle<Value> table_proxy(v8::Local<v8::String> name, const v8::AccessorInfo &info);
    
    Handle<Value> create(const Handle<Value> name);
    Handle<Value> create(const Arguments& args);
    Handle<Value> insert(const Arguments& args);
    Handle<Value> lookup(const Arguments& args);
    Handle<Value> lookup_one(const Arguments& args);
    Handle<Value> lookup_many(const Arguments& args);
    Handle<Value> lookup_query(const Arguments& args);

    Handle<Value> each(const Arguments& args);
    Handle<Value> aggregate(const Arguments& args);
    
    bool each_callback(RecordID record, Handle<Function> callback);
    shared_ptr<Table> get_cached_table(const string& db_path, const string& table_name);
  }
}

#endif
