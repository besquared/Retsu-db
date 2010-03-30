/*
 *  grouping.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/28/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_OPERATION_GROUPING_H_
#define _RETSU_OPERATION_GROUPING_H_

#include <source/Common.h>
#include <source/Table.h>
#include <source/Group.h>
#include <source/Cursor.h>

namespace Retsu {
  namespace Operation {
    using namespace v8;
    using namespace std;
    using namespace boost;
    
    class Grouping {
    public:
      Handle<Value> group(Cursor& cursor, Local<Object> params, map<size_t, Group>& groups, Handle<Array> results);
    };
  }
}

#endif