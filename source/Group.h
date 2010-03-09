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

namespace Retsu {
  using namespace std;
  
  class Group {
  public:
    vector<RecordID> records;
    map<string, string> values;
    
    double sum(const string& column);
    double count(const string& column);
    double count_unique(const string& column);
  };
}

#endif