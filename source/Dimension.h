/*
 *  Dimension.h
 *  Retsu
 *
 *  Created by Josh Ferguson on 12/10/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DIMENSION_H_
#define _RETSU_DIMENSION_H_

#include "Common.h"
#include "Errors.h"
#include "Record.h"
#include "RIDList.h"

namespace Retsu {
  using namespace std;

  class Dimension {
  public:
    string path;
    string name;
    TCHDB* database;
    
    Dimension(const string& path, const string& name);
    ~Dimension();

    /*
     * I/O Management
     */
    string Path();
    void Create();
    void Truncate();
    void Close();
    void Optimize();
    void OpenReader();
    void OpenWriter();
    bool Open(int mode);
    
    /*
     * Reading
     */
    void Lookup(const RecordID key, string& result);
    void Lookup(const RIDList& keys, vector<string>& results);
    void Lookup(const RIDList& keys, map<RecordID, string>& results);

    /*
     * Writing
     */
    bool Insert(const RecordID key, const string& value);
    
    /*
     * Error Handling
     */
    string Error();
  };
}

#endif