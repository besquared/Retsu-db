/*
 *  Measures.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measures.h"

Retsu::Measures::Measures(const fs::path& table_path) {
	this->table_path = table_path;
}

Retsu::Measures::~Measures() {
  map<string, Measure*>::iterator database;
  
  for(database = cache.begin(); database != cache.end(); database++) {
    database->second->close();
    delete(database->second);
  }
}


bool Retsu::Measures::insert(const Record& record) {
	map<string, double>::const_iterator measure;
	for(measure = record.measures.begin(); measure != record.measures.end(); measure++) {
    Measure* database = this->retrieve(measure->first);
    
    if(database != NULL) {
      database->insert(record.id, measure->second);
    } else {
      return false;
    }
	}
	
	return true;
}

Retsu::Measure* Retsu::Measures::retrieve(const string& measure, bool create) {
  map<string, Measure*>::iterator found = cache.find(measure);
  
  if(found == cache.end()) {
    Measure* database = new Measure(this->table_path.string(), measure);
    
    if(!database->exists() && !create) return NULL;
    
    database->open_writer();
    cache[measure] = database;
    return database;    
  } else {
    return found->second;
  }
}