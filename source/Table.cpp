/*
 *  Table.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Table.h"

Retsu::Table::Table(const string& database_path, const string& table_name) {
	this->database_path = fs::path(database_path);
	this->table_name = fs::path(table_name);
  
  // need a file to keep up with our id
  this->measures = new Measures(this->database_path / this->table_name);
	this->dimensions = new Dimensions(this->database_path / this->table_name);
  
  this->metadata = new Dimension((this->database_path / this->table_name).string(), "meta");
}

Retsu::Table::~Table() {
	delete(this->measures);
	delete(this->dimensions);
  delete(this->metadata);
}

bool Retsu::Table::create() {
  if(fs::create_directory(this->database_path / this->table_name)) {
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
