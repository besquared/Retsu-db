/*
 *  Table.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_TABLE_H
#define _RETSU_TABLE_H

#include "Common.h"
#include "Measures.h"
#include "Dimensions.h"

namespace Retsu {
  using namespace v8;
  using namespace std;

  class Table {
  protected:
    string path;
    string dpath;
    
  public:
    Measures* measures;
    Dimensions* dimensions;
    
    Table(const string& path, const string& dpath);
    virtual ~Table();
    
    RecordID next_id();
    void insert(const Record& record);
    void insert(const RecordID& id, const string& measure, const double& value);
    void insert(const RecordID& id, const string& dimension, const string& value);
  };
}

#endif