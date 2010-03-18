/*
 *  Cursor.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_CURSOR_H
#define _RETSU_CURSOR_H

#include "Table.h"
#include "Conditions.h"

namespace Retsu {
  using namespace v8;
  using namespace std;
  
  class Cursor {    
  public:
    bool is_conditioned;
    shared_ptr<Table> table;
    shared_ptr<Conditions> conditions;
    
    Cursor();
    Cursor(shared_ptr<Table> table);
    Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions);

    void init();
    uint64_t next();
    
  protected:
    uint64_t conditional_next();
    uint64_t unconditional_next();
  };
}

#endif