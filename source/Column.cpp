/*
 *  Column.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Column.h"

Retsu::Column::Column(const string& path, const string& name) {
  this->name = name;
  this->table_path = path;
  this->database = tchdbnew();
}

Retsu::Column::~Column() {
  close();
  tchdbdel(database);	
}

/*
 * I/O Management
 */

std::string Retsu::Column::path() {
  return (table_path / fs::path(name + ".tch")).string();
}

bool Retsu::Column::exists() {
  return fs::exists(fs::path(path()));
}

void Retsu::Column::create() {
	tchdbtune(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE);
	
  if(open(HDBOWRITER | HDBOCREAT)) {
		this->close();
	} else {
		throw StorageError("Could not create column at " + path());
	}
}

void Retsu::Column::truncate() {
	if(open(HDBOWRITER | HDBOTRUNC)) {
		close();
	} else {
		throw StorageError("Could not truncate column at " + path());
	}	
}

void Retsu::Column::close() {	
  if(!tchdbclose(this->database)){
    //		throw StorageError("Could not close dimension at " + Path());
  }
}

void Retsu::Column::optimize() {
	if(tchdbrnum(this->database) % (1<<16) == 0) {
		if(!tchdboptimize(database, -1, -1, -1, HDBTLARGE | HDBTDEFLATE)) {
      throw StorageError("Could not optimize column at " + path());
    }
	}
}

void Retsu::Column::open_reader() {
  if(!open(HDBOREADER)) {
    throw StorageError("Could not open column for reading at " + path());
  }
}

void Retsu::Column::open_writer() {
  if(!open(HDBOWRITER | HDBOCREAT)) {
    throw StorageError("Could not open column for writing at " + path());
  }
}

bool Retsu::Column::open(int mode) {
	return tchdbopen(database, path().c_str(), mode);
}

/*
 * Reading
 */ 

void Retsu::Column::lookup(const RecordID key, string& result) {
	int vsize;
	void* value = tchdbget(database, &key, sizeof(RecordID), &vsize);
	
	if(value == NULL) {
		result = string("");
	} else {
		result = string((char*)value, (size_t)vsize);
		free(value);
	}
}

void Retsu::Column::lookup(const RecordID key, double& result) {
	int vsize;
	void* value = tchdbget(database, &key, sizeof(RecordID), &vsize);
	
	if(value == NULL) {
		result = NAN;
	} else if(vsize != sizeof(double)) {
    result = NAN;
    free(value);
  } else {
		result = *((double*)value);
		free(value);
	}
}

void Retsu::Column::lookup(const RIDList& keys, vector<string>& results) {
  results.reserve(keys.size());
  
  int vsize;
  RIDList::const_iterator key;
  for(key = keys.begin(); key != keys.end(); key++) {
    void* buffer = tchdbget(database, &(*key), sizeof(RecordID), &vsize);
    
    if(buffer != NULL) {
      results.push_back("");
    } else {
      results.push_back(string((char*)buffer, (size_t)vsize));
    }
    
    free(buffer);
  }  
}

void Retsu::Column::lookup(const RIDList& keys, vector<double>& results) {
  results.reserve(keys.size());

  double buffer;
  RIDList::const_iterator key;
  for(key = keys.begin(); key != keys.end(); key++) {
    if(tchdbget3(database, &(*key), sizeof(RecordID), &buffer, sizeof(double)) != -1) {
      results.push_back(buffer);
    }
  }  
}

/*
 * Writing
 */

bool Retsu::Column::insert(const RecordID key, const string& value) {
	return tchdbput(database, &key, sizeof(RecordID), value.c_str(), value.size());
}

bool Retsu::Column::insert(const RecordID key, const double& value) {
  return tchdbput(database, &key, sizeof(RecordID), &value, sizeof(double));
}

/*
 * Error Management
 */

std::string Retsu::Column::error() {
	return string(tchdberrmsg(tchdbecode(this->database)));
}