/*
 *  Dimensions.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Dimensions.h"

Retsu::Domain::Dimensions::Dimensions(const string& path) {
	this->path = path;
}

Retsu::Domain::Dimensions::~Dimensions() {
  map<string, Data::Dimension*>::iterator database;
  
  for(database = cache.begin(); database != cache.end(); database++) {
    database->second->Close();
    delete(database->second);
  }
}

bool Retsu::Domain::Dimensions::insert(const Data::Record& record) {
	map<string, string>::const_iterator dimension;
	for(dimension = record.values.begin(); dimension != record.values.end(); dimension++) {
    Data::Dimension* database = this->retrieve(dimension->first);
    
    if(database != NULL) {
      database->Insert(record.id, dimension->second);
    } else {
      return false;
    }
	}
	
	return true;
}

Retsu::Domain::Data::Dimension* Retsu::Domain::Dimensions::retrieve(const string& dimension) {
  map<string, Data::Dimension*>::iterator found = cache.find(dimension);
  
  if(found == cache.end()) {
    Data::Dimension* database = new Data::Dimension(this->path, dimension);
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