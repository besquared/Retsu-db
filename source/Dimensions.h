/*
 *  Dimensions.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 2/21/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DIMENSIONS_H_
#define _RETSU_DIMENSIONS_H_

#include "Common.h"
#include "Record.h"
#include "Dimension.h"

namespace Retsu {
  using namespace std;

  class Dimensions {
  protected:
    string path;
    map<string, Dimension*> cache;
    
  public:
    Dimensions(const string& path);
    ~Dimensions();
    
    virtual bool insert(const Record& record);
//			virtual void Lookup(const string& dimension, const Data::RIDList& records, vector<string>& results);
    
    Dimension* retrieve(const string& dimension);
  };
}

#endif