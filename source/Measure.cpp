/*
 *  Measure.cpp
 *  Retsu
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measure.h"

Retsu::Measure::Measure(string table_path, string name) {
  this->table_path = table_path;
  this->name = name;
  this->database = tcfdbnew();
}

Retsu::Measure::~Measure() {
  close();
  tcfdbdel(database);
}

/*
 * I/O Management
 */

std::string Retsu::Measure::path() {
  return (table_path / fs::path(name + ".tcf")).string();
}

bool Retsu::Measure::exists() {
  cout << "exists" << endl;
  return fs::exists(fs::path(path()));
}

void Retsu::Measure::create() {
  cout << "create" << endl;
	tcfdbtune(database, sizeof(double), INT_MAX);

	if(this->open(FDBOWRITER | FDBOCREAT)) {
    this->close();
	} else {
    throw StorageError("Could not create measure database at " + path()  + ", " + error());
	}	
}

void Retsu::Measure::close() {
  cout << "close" << endl;
  if(!tcfdbclose(database)) {
//		throw StorageError("Could not close measure at " + Path());
  }
}

void Retsu::Measure::truncate() {
  cout << "truncate" << endl;
	if(!open(FDBOWRITER | FDBOTRUNC)) {
		this->close();
	} else {
		throw StorageError("Could not truncate measure at " + path());
	}	
}

void Retsu::Measure::open_reader() {
  cout << "open_reader" << endl;
  if(!open(FDBOREADER)) {
    throw StorageError("Could not open measure for reading at " + path());
  }
}

void Retsu::Measure::open_writer() {
  cout << "open_writer" << endl;
  if(!open(FDBOWRITER | FDBOCREAT)) {
    throw StorageError("Could not open measure for writing at " + path());
  }
}

bool Retsu::Measure::open(int mode) {
  cout << "open " << path() << endl;
	return tcfdbopen(database, path().c_str(), mode);
}

/*
 * Reading
 */ 

bool Retsu::Measure::lookup(RecordID key, double& result) {
	int size_v;
	void* value = tcfdbget(database, key, &size_v);
	
	if(value == NULL) {
		return false;
	} else {
		result = *((double*)(value));
		free(value);
		return true;
	}
}

void Retsu::Measure::lookup(const RIDList& keys, vector<double>& results) {
	results.reserve(keys.size());
	
	double buffer;
	RIDList::const_iterator key;
	for(key = keys.begin(); key != keys.end(); key++) {
		if(tcfdbget4(database, *key, &buffer, sizeof(double)) != -1) {
			results.push_back(buffer);
		}
	}
}

/*
 * Writing
 */

bool Retsu::Measure::insert(RecordID key, double value) {
	return tcfdbput(database, key, &value, sizeof(double));
}

/*
 * Error Management
 */

std::string Retsu::Measure::error() {
	return string(tcfdberrmsg(tcfdbecode(database)));
}