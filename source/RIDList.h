/*
 *  RIDList.h
 *  Retsu
 *
 *  Created by Josh Ferguson on 12/17/09.
 *  Copyright 2009 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_RID_LIST_H_
#define _RETSU_RID_LIST_H_

#include "Common.h"

namespace Retsu {
  using namespace std;
  
  class RIDList : public vector<RecordID> {
  public:
    RIDList operator&(RIDList& other);
    RIDList operator|(RIDList& other);
    
    friend ostream& operator<<(ostream& out, const RIDList& records) {
      out << "[";
      for(size_t i = 0; i < records.size(); i++) {
        out << records[i];
        if(i < records.size() - 1) out << ", "; 
      }
      out << "]";
      return out;
    }				
  };
}

#endif