/*
 *  Group.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_GROUP_H_
#define _RETSU_GROUP_H_

#include "Common.h"
#include "Record.h"
#include "Table.h"
#include "RIDList.h"

namespace Retsu {
  using namespace std;
  using namespace v8;
  using namespace boost;
  
  class Group {
  public:
    RIDList records;
    shared_ptr<Table> table;
    map<string, string> values;
    map<string, double> aggregates;
    
    Group();
    Group(shared_ptr<Table> table);
    
    double count();
    double sum(const string& column);
    double average(const string& column);
    double count_unique(const string& column);
    double aggregate(Handle<Function> aggfunc);
    
    void lookup(const string& column, vector<double>& results);
  };
}

#endif