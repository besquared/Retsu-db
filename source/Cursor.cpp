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
  current = 0;
  sampled = 0;
  srand(time(NULL));
  table->cursor_init();
}

bool Retsu::Cursor::next() {
  if(is_conditioned) {
    return conditional_next();
  } else {
    return unconditional_next();
  }
}

bool Retsu::Cursor::conditional_next() {
  int vsize;
  set<string>::iterator column;

  while(true) {
    if(!unconditional_next()) { return false; }
    
    for(column = conditions->columns.begin(); column != conditions->columns.end(); column++) {
      // do a raw lookup here
      void* datum = table->lookup(*column, current, vsize);
      
      // TODO have a way to deal with NULL's in conditions
      if(datum == NULL) { continue; }
      
      if(conditions->check(*column, datum, vsize)) {
        free(datum);
        return true;
      } else {
        free(datum);
        break;
      }
    }
  }
}

bool Retsu::Cursor::unconditional_next() {
  if(is_sampled && sample_size < population_size) {
    if(sampled == sample_size) {
      return false;
    } else {
      sampled++;
      current = rand() % population_size + 1;
      return true;
    }
  } else {
    return table->cursor_next();
  }
}

/*
 * Table access wrappers
 */

void* Retsu::Cursor::lookup(const string& column, int& vsize, bool create) {
  return table->lookup(column, current, vsize, create);
}

void Retsu::Cursor::lookup(const string& column, string& result, bool create) {
  table->lookup(column, current, result, create);
}

void Retsu::Cursor::lookup(const string& column, double& result, bool create) {
  table->lookup(column, current, result, create);
}