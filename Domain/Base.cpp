/*
 *  Base.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Base.h"

Retsu::Domain::Base::Base(const string& path, const string& dpath) {
	this->path = path;
	this->dpath = dpath;
  this->measures = new Domain::Measures(this->dpath);
	this->dimensions = new Domain::Dimensions(this->dpath);
}

Retsu::Domain::Base::~Base() {
	delete(this->measures);
	delete(this->dimensions);
}

void Retsu::Domain::Base::insert(const Data::Record& record) {
  this->measures->insert(record);
  this->dimensions->insert(record);
}
