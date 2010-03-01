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
  // need a file to keep up with our id
  this->measures = new Measures(this->dpath);
	this->dimensions = new Dimensions(this->dpath);
}

Retsu::Table::~Table() {
	delete(this->measures);
	delete(this->dimensions);
}

double Retsu::Table::next_id() {
  return 100;
}

void Retsu::Table::insert(const Record& record) {
  this->measures->insert(record);
  this->dimensions->insert(record);
}

void Retsu::Table::insert(const RecordID& id, const string& dimension, const string& value) {
  Dimension* database = dimensions->retrieve(dimension);
  
  if(database != NULL) {
    database->Insert(id, value);
  } else {
    return;
  }
}

void Retsu::Table::insert(const RecordID& id, const string& measure, const double& value) {
  
}
