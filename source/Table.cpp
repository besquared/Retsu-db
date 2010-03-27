/*
 *  Table.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Table.h"

Retsu::Table::Table(const string& data_path, const string& table_name) {
	this->data_path = fs::path(data_path);
	this->table_name = fs::path(table_name);
  
  this->records = new Records(this->data_path / this->table_name);
  
  this->records->open_writer();
}

Retsu::Table::~Table() {
  delete(records);
}

// make this static, wtf mate
void Retsu::Table::create(const string& data_path, const string& table_name) {
  fs::path full_path = fs::path(data_path) / fs::path(table_name);
  
  if(fs::exists(full_path) || fs::create_directory(full_path)) {
    Records::create(full_path);
  } else {
    throw StorageError("Could not create table directory at " + full_path.string());
  }
}

void Retsu::Table::lookup(const string& column, const RecordID& id, string& result, bool create) {
  shared_ptr<Column> database = cache_get(column, create);
  
  if(database == NULL) {
    throw DimensionNotFoundError("Could not find column " + column + " in table " + table_name.string());
  } else {
    database->lookup(id, result);
  }
}

void Retsu::Table::lookup(const string& column, const RecordID& id, double& result, bool create) {
  shared_ptr<Column> database = cache_get(column, create);
  
  if(database == NULL) {
    throw DimensionNotFoundError("Could not find column " + column + " in table " + table_name.string());
  } else {
    database->lookup(id, result);
  }
}

void* Retsu::Table::lookup(const string& column, const RecordID& id, int& vsize, bool create) {
  shared_ptr<Column> database = cache_get(column, create);
  
  if(database == NULL) {
    throw DimensionNotFoundError("Could not find column " + column + " in table " + table_name.string());
  } else {
    return database->lookup(id, vsize);
  }  
}

void Retsu::Table::lookup(const string& column, const RIDList& records, vector<double>& results, bool create) {
  shared_ptr<Column> database = cache_get(column, create);
  
  if(database == NULL) {
    throw DimensionNotFoundError("Could not find column " + column + " in table " + table_name.string());
  } else {
    database->lookup(records, results);
  }
}

void Retsu::Table::lookup(const string& column, const RIDList& records, vector<string>& results, bool create) {
  shared_ptr<Column> database = cache_get(column, create);
  
  if(database == NULL) {
    throw DimensionNotFoundError("Could not find column " + column + " in table " + table_name.string());
  } else {
    database->lookup(records, results);
  }
}

void Retsu::Table::insert(const string& column, const RecordID& id, const string& value) {
  shared_ptr<Column> database = cache_get(column);

  if(database != NULL) {
    records->insert(id);
    database->insert(id, value);
  }
}

void Retsu::Table::insert(const string& column, const RecordID& id, const double& value) {
  shared_ptr<Column> database = cache_get(column);
  
  if(database != NULL) {
    records->insert(id);
    database->insert(id, value);
  }
}

/*
 * Auto Increment
 */

uint64_t Retsu::Table::size() {
  return records->size();
}

double Retsu::Table::next_id() {
  return size() + 1;
}

/*
 * Cursors
 */

void Retsu::Table::cursor_init() {
  records->cursor_init();
}

uint64_t Retsu::Table::cursor_next() {
  return records->cursor_next();
}

/*
 * Cache Management
 */

boost::shared_ptr<Retsu::Column> Retsu::Table::cache_set(const string& column, bool create) {
  fs::path full_path = data_path / table_name;
  shared_ptr<Column> database(new Column(full_path.string(), column));
  
  if(database->exists()) {
    database->open_writer();
  } else if(create) {
    database->create();
    database->open_writer();
  } else {
    return shared_ptr<Column>();
  }
  
  columns[column] = database;
  return database;
}

boost::shared_ptr<Retsu::Column> Retsu::Table::cache_get(const string& column, bool create) {
  map< string, shared_ptr<Column> >::iterator found = columns.find(column);
  
  if(found == columns.end()) {
    return cache_set(column, create);
  } else {
    return found->second;
  }
}