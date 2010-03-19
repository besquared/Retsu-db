/*
 *  Column.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/18/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_COLUMN_H_
#define _RETSU_COLUMN_H_

#include "Common.h"
#include "Errors.h"
#include "RIDList.h"

namespace Retsu {
  using namespace std;
  
  class Column {
  protected:    
    TCHDB* database;

  public:
    string name;
    fs::path table_path;
    
    Column(const string& path, const string& name);
    ~Column();
    
    /*
     * I/O Management
     */
    string path();
    bool exists();
    void create();
    void truncate();
    void close();
    void optimize();
    void open_reader();
    void open_writer();
    bool open(int mode);
    
    /*
     * Reading
     */
    void lookup(const RecordID key, string& result);
    void lookup(const RecordID key, double& result);
    void lookup(const RIDList& keys, vector<string>& results);
    void lookup(const RIDList& keys, vector<double>& results);

    /*
     * Writing
     */
    bool insert(const RecordID key, const string& value);
    bool insert(const RecordID key, const double& value);
    
    /*
     * Error Handling
     */
    string error();
  };
}

#endif