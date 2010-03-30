/*
 *  Group.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "Group.h"

//double Retsu::Group::sum(const string& column) {
//  vector<double> values;
//  table->lookup(column, records, values, false);
//    
//  double result = 0;
//  for(size_t i = 0; i < values.size(); i++) {
//    result += values[i];
//  }
//  
//  return result;
//}
//
//double Retsu::Group::average(const string& column) {
//  vector<double> values;
//  table->lookup(column, records, values, false);
//  
//  double sum = 0;
//  double count = 0;
//  for(size_t i = 0; i < values.size(); i++) {
//    sum += values[i];
//    count++;
//  }
//  
//  if(count > 0) {
//    return sum / count;
//  } else {
//    return 0.0;
//  }
//}
//
//double Retsu::Group::count() {
//  return records.size();
//}
//
//double Retsu::Group::count_unique(const string& column) {
//  return 0.0;
//}
//
//double Retsu::Group::aggregate(Handle<Function> aggfunc) {
//  return 0.0;
//}