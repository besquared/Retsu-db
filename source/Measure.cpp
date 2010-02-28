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

bool Retsu::Measure::Create() {	
	tcfdbtune(this->database, sizeof(double), INT_MAX);
	
	if(this->Open(FDBOWRITER | FDBOCREAT)) {
		this->Close();
		return true;
	} else {
		return false;
	}	
}

bool Retsu::Measure::Close() {
  if(tcfdbclose(this->database)){
		return true;
  } else {
    return false;
  }
}

bool Retsu::Measure::Truncate() {
	if(this->Open(FDBOWRITER | FDBOTRUNC)) {
		this->Close();
		return true;
	} else {
		return false;
	}	
}

bool Retsu::Measure::OpenReader() {
  return this->Open(FDBOREADER);
}

bool Retsu::Measure::OpenWriter() {
  return this->Open(FDBOWRITER | FDBOCREAT);
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