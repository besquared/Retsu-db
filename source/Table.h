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
#include "Metadata.h"

namespace Retsu {
  using namespace v8;
  using namespace std;
  
  class Table {
  protected:
    fs::path database_path;
    fs::path table_name;
    
  public:
    Measures* measures;
    Dimensions* dimensions;
    Metadata* metadata;
    
    Table(const string& database_path, const string& table_name);
    virtual ~Table();
    
    static bool create(const string& database_path, const string& table_name);
    
    RecordID next_id();
    void insert(const Record& record);
    void insert(const RecordID& id, const string& measure, const double& value);
    void insert(const RecordID& id, const string& dimension, const string& value);
    
    v8::Handle<v8::Value> lookup(const RecordID& id, const string& column);
  };
}

#endif