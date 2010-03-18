/*
 *  Cursor.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Cursor.h"

Retsu::Cursor::Cursor() {}

Retsu::Cursor::Cursor(shared_ptr<Table> table) {
  this->table = table;
  this->is_conditioned = false;
  
  init();
}

Retsu::Cursor::Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions) {
  this->table = table;
  this->conditions = conditions;
  this->is_conditioned = true;
  
  init();
}

void Retsu::Cursor::init() {
  this->table->cursor_init();
}

uint64_t Retsu::Cursor::next() {
  if(is_conditioned) {
    return conditional_next();
  } else {
    return unconditional_next();
  }
}

uint64_t Retsu::Cursor::conditional_next() {
  string value;
  set<string>::iterator column;
  uint64_t record_id;
  
  while(true) {
    record_id = unconditional_next();
    if(record_id == 0) { return 0; }
    
    for(column = conditions->columns.begin(); column != conditions->columns.end(); column++) {
      table->lookup(record_id, *column, value);
      
      if(value.empty()) { continue; }

      if(conditions->check(*column, value)) {
        return record_id;
      }
    }
  }
}

uint64_t Retsu::Cursor::unconditional_next() {
  return table->cursor_next();
}

