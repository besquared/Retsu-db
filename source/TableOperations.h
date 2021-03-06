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
#include "Group.h"
#include "Cursor.h"
#include "TableManager.h"

#include <source/operation/mean.h>

namespace Retsu {  
  namespace TableOperations {
    using namespace v8;
    using namespace std;
    using namespace boost;

    void install(Handle<ObjectTemplate> scope);
    Handle<Value> get_table_proxy(v8::Local<v8::String> name, const v8::AccessorInfo &info);
    
    Handle<Value> create(const Arguments& args);
    Handle<Value> drop(const Arguments& args);
    Handle<Value> insert(const Arguments& args);
    Handle<Value> lookup(const Arguments& args);
    Handle<Value> lookup_one(const Arguments& args);
    Handle<Value> lookup_many(const Arguments& args);
    Handle<Value> lookup_query(const Arguments& args);
    Handle<Value> get_record_data(Local<String> name, const AccessorInfo& info);

    Handle<Value> each(const Arguments& args);
    Handle<Value> mean(const Arguments& args);
  }
}

#endif
