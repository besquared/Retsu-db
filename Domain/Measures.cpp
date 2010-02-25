/*
 *  Measures.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measures.h"

Retsu::Domain::Measures::Measures(const string& path) {
	this->path = path;
}

Retsu::Domain::Measures::~Measures() {
  map<string, Data::Measure*>::iterator database;
  
  for(database = cache.begin(); database != cache.end(); database++) {
    database->second->Close();
    delete(database->second);
  }
}


bool Retsu::Domain::Measures::insert(const Data::Record& record) {
	map<string, double>::const_iterator measure;
	for(measure = record.measures.begin(); measure != record.measures.end(); measure++) {
    Data::Measure* database = this->retrieve(measure->first);
    
    if(database != NULL) {
      database->Insert(record.id, measure->second);
    } else {
      return false;
    }
	}
	
	return true;
}

Retsu::Domain::Data::Measure* Retsu::Domain::Measures::retrieve(const string& measure) {
  map<string, Data::Measure*>::iterator found = cache.find(measure);
  
  if(found == cache.end()) {
    Data::Measure* database = new Data::Measure(this->path, measure);
    if(database->OpenWriter()) {
      cache[measure] = database;
      return database;
    } else {
      return NULL;
    }
  } else {
    return found->second;
  }
}