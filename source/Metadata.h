/*
 *  Metadata.h
 *  Flow
 *
 *  Created by Josh Ferguson on 12/14/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_METADATA_H_
#define _RETSU_METADATA_H_

#include "Common.h"
#include "Record.h"
#include "RIDList.h"

namespace Retsu {
  using namespace std;

  class Metadata {
  protected:
    fs::path table_path;
    TCBDB *database;
    
  public:
    Metadata(const fs::path& table_path);
    virtual ~Metadata();
    
    virtual bool OpenReader();
    virtual bool OpenWriter();
    virtual bool Open(int mode);
    virtual bool Close();
    virtual bool Truncate();
    
    virtual bool Get(const string& key, string& result);
    virtual bool Get(const string& key, set<string>& results);
    virtual bool Get(const string& key, vector<string>& results);
    virtual bool Get(const string& key, RIDList& results);
    
    virtual bool Put(const string& key, const string& value);
    virtual bool PutDup(const string& key, const string& value);
    virtual bool PutDup(const string& key, const RecordID& record);
    virtual bool PutCat(const string& key, const RecordID& record);
    
    virtual bool Add(const string& key, const int value, int& result);
    virtual bool Add(const string& key, const double value, double& result);
    
    string Error();
    int ErrorCode();
    
    static bool Create(const fs::path& table_path);
    static string Path(const fs::path& table_path);
  };
}

#endif