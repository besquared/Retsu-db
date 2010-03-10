/*
 *  Measure.h
 *  Retsu
 *
 *  Created by Josh Ferguson on 11/26/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_MEASURE_H_
#define _RETSU_MEASURE_H_

#include "Common.h"
#include "Errors.h"
#include "RIDList.h"

namespace Retsu {
  using namespace std;

  class Measure {
  public:
    fs::path table_path;
    string name;
    TCFDB* database;
    
    Measure(string path, string name);
    ~Measure();

    /*
     * I/O Management
     */
    string path();
    bool exists();
    void create();
    void close();
    void truncate();
    void open_reader();
    void open_writer();
    bool open(int mode);

    /*
     * Reading
     */
    bool lookup(RecordID key, double& result);
    void lookup(const RIDList& keys, vector<double>& results);
    
    /*
     * Writing
     */
    bool insert(RecordID key, double value);
    
    /*
     * Error Handling
     */
    string error();
  };
}

#endif