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

bool Retsu::Domain::Dimensions::insert(const Data::Record& record) {
	map<string, string>::const_iterator dimension;
	for(dimension = record.values.begin(); dimension != record.values.end(); dimension++) {
		Data::Dimension database(this->path, dimension->first);
    
		if(!database.OpenWriter()) {
			return false;
		}
		
		if(!database.Insert(record.id, dimension->second)) {
			database.Close();
			return false;
		}
		
		database.Close();
	}
	
	return true;
}