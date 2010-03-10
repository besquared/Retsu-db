/*
 *  Group.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Group.h"

Retsu::Group::Group() {}

Retsu::Group::Group(shared_ptr<Retsu::Table> table) {
  this->table = table;
}

double Retsu::Group::sum(const string& name, const string& column) {
  Measure* measure_db = table->measures->retrieve(column, false);
  
  cout << "Summing the grizoup!" << endl;
  
  if(measure_db == NULL) {
    cout << "Throwing a mighty error!" << endl;
    throw DimensionNotFoundError("Could not find measure " + column);
  } else {
    cout << "FOR SHIZZLE MY SUMIZZLE" << endl;
    vector<double> values;
    measure_db->Lookup(records, values);
    
    double result = 0;
    for(size_t i = 0; i < values.size(); i++) {
      result += values[i];
    }
    return result;
  }
}

double Retsu::Group::average(const string& name, const string& column) {
  return 0.0;
}

double Retsu::Group::count(const string& name, const string& column) {
  if(column == "*") {
    return records.size();
  } else {
    return 0.0;
  }
}
double Retsu::Group::count_unique(const string& name, const string& column) {
  return 0.0;
}

double Retsu::Group::aggregate(const string& name, Handle<Function> aggfunc) {
  return 0.0;
}
