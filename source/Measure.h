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
#include "RIDList.h"

namespace Retsu {
  using namespace std;

  class Measure {
  public:
    string path;
    string name;
    TCFDB* database;
    
    Measure(string path, string name);
    ~Measure();

    /*
     * I/O Management
     */
    string Path();
    bool Create();
    bool Close();
    bool Truncate();
    bool OpenReader();
    bool OpenWriter();
    bool Open(int mode);
    
    /*
     * Reading
     */
    bool Lookup(RecordID key, double& result);
    void Lookup(const RIDList& keys, vector<double>& results);
    
    /*
     * Writing
     */
    bool Insert(RecordID key, double value);
    
    /*
     * Error Handling
     */
    string Error();
  };
}

#endif