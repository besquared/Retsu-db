/*
 *  Measures.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_MEASURES_H_
#define _RETSU_MEASURES_H_

#include "Common.h"
#include "Measure.h"

namespace Retsu {
  using namespace std;

  class Measures {
  protected:
    fs::path table_path;
    map<string, Measure*> cache;

  public:		
    Measures(const fs::path& table_path);
    ~Measures();
    
    bool insert(const Record& record);
//			virtual void Lookup(const string& measure, const RIDList& records, vector<double>& results);
    
    Measure* retrieve(const string& measure, bool create = true);
  };
}

#endif