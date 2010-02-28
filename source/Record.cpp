/*
 *  Record.cpp
 *  Retsu
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Record.h"

Retsu::Record::Record(RecordID id) {
  this->id = id;
}

Retsu::Record::~Record() {}

void Retsu::Record::insert(const string& key, const string& value) {
  this->values[key] = value;
}

void Retsu::Record::insert(const string& key, const double& value) {
  this->measures[key] = value;
}