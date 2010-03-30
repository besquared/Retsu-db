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
  protected:
    shared_ptr<Table> table;
    shared_ptr<Conditions> conditions;

  public:
    RecordID current;
    bool is_sampled;
    bool is_conditioned;

    size_t sampled;
    size_t sample_size;
    size_t population_size;
    
    Cursor();
    Cursor(shared_ptr<Table> table);
    Cursor(shared_ptr<Table> table, size_t sample_size);
    Cursor(shared_ptr<Table> table, Conditions& conditions);
    Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions);
    Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions, size_t sample_size);

    void init();
    bool next();
    
    void* lookup(const string& column, int& vsize, bool create = true);
    void lookup(const string& column, string& result, bool create = true);
    void lookup(const string& column, double& result, bool create = true);
  protected:
    bool conditional_next();
    bool unconditional_next();
  };
}

#endif