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
     * Iteration
     */
    void cursor_init();
    uint64_t cursor_next();
    
    /*
     * Writing
     */
    void insert(const RecordID& key);
    void remove(const RecordID& key);
    
    /*
     * Other
     */
    uint64_t size();
  };
}

#endif