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

bool Retsu::Domain::Measures::insert(const Data::Record& record) {
	map<string, double>::const_iterator measure;
	for(measure = (*record.measures).begin(); measure != (*record.measures).end(); measure++) {
		Data::Measure database(this->path, measure->first);

		if(!database.OpenWriter()) {
			return false;
		}
    
		if(!database.Insert(record.id, measure->second)) {
			database.Close();
			return false;
		}
	}
	
	return true;
}