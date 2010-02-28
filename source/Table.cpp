/*
 *  Table.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Table.h"

Retsu::Table::Table(const string& path, const string& dpath) {
	this->path = path;
	this->dpath = dpath;
  this->measures = new Measures(this->dpath);
	this->dimensions = new Dimensions(this->dpath);
}

Retsu::Table::~Table() {
	delete(this->measures);
	delete(this->dimensions);
}

void Retsu::Table::insert(const Record& record) {
  this->measures->insert(record);
  this->dimensions->insert(record);
}
