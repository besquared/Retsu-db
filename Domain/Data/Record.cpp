/*
 *  Record.cpp
 *  Retsu
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Record.h"

Retsu::Domain::Data::Record::Record(RecordID id) {
  this->id = id;
  this->measures = new map<string, double>();
}

Retsu::Domain::Data::Record::~Record() {
  delete(this->measures);
}

void Retsu::Domain::Data::Record::insert(const string& key, const string& value) {
  this->values[key] = value;
}

void Retsu::Domain::Data::Record::insert(const string& key, const double& value) {
  this->measures->insert(pair<string, double>(key, value));
}