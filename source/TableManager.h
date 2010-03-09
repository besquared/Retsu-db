/*
 *  TableManager.h
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#ifndef _RETSU_TABLE_MANAGER_H_
#define _RETSU_TABLE_MANAGER_H_

#include "Common.h"
#include "Table.h"

namespace Retsu {
  using namespace std;
  using namespace boost;
  
  typedef map< string, shared_ptr<Table> > TableCache;

  class TableManager {
  public:
    TableCache table_cache;
    
    static TableManager& instance() {
      static TableManager tableManager;
      return tableManager;
    }
    
    shared_ptr<Table> get(const string& table_name);
    
    // create
    // drop
    // list
    
    /* more (non-static) functions here */
  private:
    TableManager(); // ctor hidden
    TableManager(TableManager const&); // copy ctor hidden
    TableManager& operator=(TableManager const&); // assign op. hidden
    ~TableManager(); // dtor hidden
  };
}

#endif