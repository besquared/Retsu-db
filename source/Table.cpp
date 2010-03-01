/*
 *  Table.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Table.h"

Retsu::Table::Table(const string& root_path, const string& table_path) {
	this->root_path = fs::path(root_path);
	this->table_path = fs::path(table_path);
  
  // need a file to keep up with our id
  this->measures = new Measures(this->root_path / this->table_path);
	this->dimensions = new Dimensions(this->root_path / this->table_path);
}

Retsu::Table::~Table() {
	delete(this->measures);
	delete(this->dimensions);
}

bool Retsu::Table::create() {
  if(fs::create_directory(this->root_path / this->table_path)) {
    return true;
  } else {
    return false;
  }
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
