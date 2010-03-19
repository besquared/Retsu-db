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
#include "Records.h"
#include "Column.h"
#include "Measures.h"
#include "Dimensions.h"
#include "Conditions.h"

namespace Retsu {
  using namespace v8;
  using namespace std;
  
  class Table {
  protected:
    fs::path data_path;
    fs::path table_name;
    
    Records* records;
    map< string, shared_ptr<Column> > columns;

  public:    
    Table(const string& data_path, const string& table_name);
    virtual ~Table();
    
    /*
     * Lifecycle
     */
    static void create(const string& data_path, const string& table_name);
    
    /*
     * Reading & Writing
     */
    void lookup(const string& column, const RecordID& id, string& result, bool create = true);
    void lookup(const string& column, const RecordID& id, double& result, bool create = true);
    void lookup(const string& column, const RIDList& records, vector<string>& results, bool create = true);
    void lookup(const string& column, const RIDList& records, vector<double>& results, bool create = true);

    void insert(const string& column, const RecordID& id, const string& value);
    void insert(const string& column, const RecordID& id, const double& value);
    
    /*
     * Auto Increment
     */
    uint64_t size();
    RecordID next_id();
    
    /*
     * Cursors
     */
    void cursor_init();
    uint64_t cursor_next();
    
    /*
     * Cache Management
     */
    shared_ptr<Column> cache_set(const string& column);
    shared_ptr<Column> cache_get(const string& column, bool create = true);
  };
}

#endif