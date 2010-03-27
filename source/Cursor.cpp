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
  this->is_sampled = false;
  this->is_conditioned = false;
  
  init();
}

Retsu::Cursor::Cursor(shared_ptr<Table> table, size_t sample_size) {
  this->table = table;
  this->is_sampled = true;
  this->is_conditioned = false;
  this->sample_size = sample_size;
  this->population_size = table->size();
  
  init();
}


Retsu::Cursor::Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions) {
  this->table = table;
  this->is_conditioned = true;
  this->conditions = conditions;
  this->is_sampled = false;
  
  init();
}

Retsu::Cursor::Cursor(shared_ptr<Table> table, shared_ptr<Conditions> conditions, size_t sample_size) {
  this->table = table;
  this->is_conditioned = true;
  this->conditions = conditions;
  
  this->is_sampled = true;
  this->sample_size = sample_size;
  this->population_size = table->size();
  
  init();
}

void Retsu::Cursor::init() {
  sampled = 0;
  srand(time(NULL));
  table->cursor_init();
}

uint64_t Retsu::Cursor::next() {
  if(is_conditioned) {
    return conditional_next();
  } else {
    return unconditional_next();
  }
}

uint64_t Retsu::Cursor::conditional_next() {
  int vsize;
  uint64_t record_id;
  set<string>::iterator column;

  while(true) {
    record_id = unconditional_next();
    if(record_id == 0) { return 0; }
    
    // I need to know about the column conditions
    //  to know how I'm supposed to read the data here
    for(column = conditions->columns.begin(); column != conditions->columns.end(); column++) {
      // do a raw lookup here
      void* datum = table->lookup(*column, record_id, vsize);
      
      // TODO have a way to deal with NULL's in conditions
      if(datum == NULL) { continue; }
      
      if(conditions->check(*column, datum, vsize)) {
        free(datum);
        return record_id;
      } else {
        free(datum);
        break;
      }
    }
  }
}

uint64_t Retsu::Cursor::unconditional_next() {
  if(is_sampled && sample_size < population_size) {
    if(sampled == sample_size) {
      return 0;
    } else {
      sampled++;
      return rand() % population_size + 1;
    }
  } else {
    return table->cursor_next();
  }
}
