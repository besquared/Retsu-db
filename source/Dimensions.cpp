/*
 *  Dimensions.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimensions.h"

Retsu::Dimensions::Dimensions(const string& path) {
	this->path = path;
}

Retsu::Dimensions::~Dimensions() {
  map<string, Dimension*>::iterator database;
  
  for(database = cache.begin(); database != cache.end(); database++) {
    database->second->Close();
    delete(database->second);
  }
}

bool Retsu::Dimensions::insert(const Record& record) {
	map<string, string>::const_iterator dimension;
	for(dimension = record.values.begin(); dimension != record.values.end(); dimension++) {
    Dimension* database = this->retrieve(dimension->first);
    
    if(database != NULL) {
      database->Insert(record.id, dimension->second);
    } else {
      return false;
    }
	}
	
	return true;
}

Retsu::Dimension* Retsu::Dimensions::retrieve(const string& dimension) {
  map<string, Dimension*>::iterator found = cache.find(dimension);
  
  if(found == cache.end()) {
    Dimension* database = new Dimension(this->path, dimension);
    if(database->OpenWriter()) {
      cache[dimension] = database;
      return database;
    } else {
      return NULL;
    }
  } else {
    return found->second;
  }
}