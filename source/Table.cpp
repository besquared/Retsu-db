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
  
  this->records = new Records(this->database_path);
  this->measures = new Measures(this->database_path / this->table_name);
	this->dimensions = new Dimensions(this->database_path / this->table_name);
  
  this->records->open_writer();
}

Retsu::Table::~Table() {
  delete(this->records);
	delete(this->measures);
	delete(this->dimensions);
}

// make this static, wtf mate
void Retsu::Table::create(const string& database_path, const string& table_name) {
  fs::path full_path = fs::path(database_path) / fs::path(table_name);
  
  if(fs::exists(full_path) || fs::create_directory(full_path)) {
    Records::create(full_path);
  } else {
    throw StorageError("Could not create table directory at " + full_path.string());
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
    records->insert(id);
    database->Insert(id, value);
  } else {
    return;
  }
}

void Retsu::Table::insert(const RecordID& id, const string& measure, const double& value) {
  Measure* database = measures->retrieve(measure);
  
  if(database != NULL) {
    database->Insert(id, value);
  } else {
    return;
  }  
}

v8::Handle<v8::Value> Retsu::Table::lookup(const RecordID& id, const string& column) {
  Dimension* dimension_db = dimensions->retrieve(column);
  
  if(dimension_db == NULL) {
    Measure* measure_db = measures->retrieve(column);
    
    if(measure_db == NULL) {
      return Handle<Value>();
    } else {
      double value = 0;
      measure_db->Lookup(id, value);
      return Number::New(value);
    }
  } else {
    string value;
    dimension_db->Lookup(id, value);
    return String::New(value.c_str());
  }
}
