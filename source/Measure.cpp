/*
 *  Measure.cpp
 *  Retsu
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Measure.h"

Retsu::Measure::Measure(string path, string name) {
  this->path = path;
  this->name = name;
  this->database = tcfdbnew();
}

Retsu::Measure::~Measure() {
  this->Close();
  tcfdbdel(this->database);
}

/*
 * I/O Management
 */

std::string Retsu::Measure::Path() {
  return this->path + "/" + this->name + ".tcf";
}

bool Retsu::Measure::Exists() {
  if(this->Open(FDBOREADER)) {
    this->Close();
    return true;
  } else {
    return false;
  }
}

void Retsu::Measure::Create() {	
	tcfdbtune(this->database, sizeof(double), INT_MAX);
	
	if(this->Open(FDBOCREAT)) {
    this->Close();
	} else {
    throw StorageError("Could not create measure database at " + Path());
	}	
}

void Retsu::Measure::Close() {
  if(!tcfdbclose(this->database)) {
//		throw StorageError("Could not close measure at " + Path());
  }
}

void Retsu::Measure::Truncate() {
	if(!this->Open(FDBOWRITER | FDBOTRUNC)) {
		this->Close();
	} else {
		throw StorageError("Could not truncate measure at " + Path());
	}	
}

void Retsu::Measure::OpenReader() {
  if(!this->Open(FDBOREADER)) {
    throw StorageError("Could not open measure for reading at " + Path());
  }
}

void Retsu::Measure::OpenWriter() {
  if(!this->Open(FDBOWRITER)) {
    throw StorageError("Could not open measure for writing at " + Path());
  }
}

bool Retsu::Measure::Open(int mode) {
	return tcfdbopen(this->database, this->Path().c_str(), mode);
}

/*
 * Reading
 */ 

bool Retsu::Measure::Lookup(RecordID key, double& result) {
	int size_v;
	void* value = tcfdbget(this->database, key, &size_v);
	
	if(value == NULL) {
		return false;
	} else {
		result = *((double*)(value));
		free(value);
		return true;
	}
}

void Retsu::Measure::Lookup(const RIDList& keys, vector<double>& results) {
	results.reserve(keys.size());
	
	double buffer;
	RIDList::const_iterator key;
	for(key = keys.begin(); key != keys.end(); key++) {
		if(tcfdbget4(this->database, *key, &buffer, sizeof(double)) != -1) {
			results.push_back(buffer);
		}
	}
}

/*
 * Writing
 */

bool Retsu::Measure::Insert(RecordID key, double value) {
	return tcfdbput(this->database, key, &value, sizeof(double));
}

/*
 * Error Management
 */

std::string Retsu::Measure::Error() {
	return string(tcfdberrmsg(tcfdbecode(this->database)));
}