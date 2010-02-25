/*
 *  Record.h
 *  Retsu
 *
 *  Created by Josh Ferguson on 12/20/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_DOMAIN_DATA_RECORD_H_
#define _RETSU_DOMAIN_DATA_RECORD_H_

#include <Common.h>

namespace Retsu {
  typedef double RecordID;

  namespace Domain {
    namespace Data {
      using namespace std;

      class Record {
      public:
        RecordID id;
        map<string, string> values;
        map<string, double> measures;
        
        Record(RecordID id);
        
        void insert(const string& key, const string& value);
        void insert(const string& key, const double& value);
      };
    }
  }
}

#endif