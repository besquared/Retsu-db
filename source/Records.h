/*
 *  Records.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/3/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_RECORDS_H_
#define _RETSU_RECORDS_H_

#include "Common.h"
#include "Record.h"
#include "Errors.h"

namespace Retsu {
  class Records {
  public:
    TCFDB* database;    
    fs::path table_path;

    Records(const fs::path& table_path);
    ~Records();
    
    /*
     * I/O Management
     */
    string path();
    void close();
    void truncate();
    void open_reader();
    void open_writer();
    bool open(int mode);
    static void create(const fs::path& table_path);
    
    /*
     * Reading
     */
    void each(bool (*eachfunc)(RecordID));
    void each(bool (*eachfunc)(RecordID, Handle<ObjectTemplate>, Handle<Function>));
    /*
     * Writing
     */
    void insert(const RecordID& key);
    void remove(const RecordID& key);
  };
}

#endif