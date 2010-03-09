/*
 *  TableManager.cpp
 *  retsudb
 *
 *  Created by Josh Ferguson on 3/8/10.
 *  Copyright 2010 Cube Tree Labs, LLC. All rights reserved.
 *
 */

#include "TableManager.h"

Retsu::TableManager::TableManager() {}
Retsu::TableManager::~TableManager() {}
Retsu::TableManager::TableManager(TableManager const&) {}
//Retsu::TableManager::TableManager& operator=(TableManager const&) {}

boost::shared_ptr<Retsu::Table> Retsu::TableManager::get(const string& table_name) {
  string db_path = ".";
  string key = db_path + "/" + table_name;
  
  TableCache::iterator found = table_cache.find(key);

  if(found == table_cache.end()) {
    shared_ptr<Table> table(new Table(db_path, table_name)); 
    table_cache[key] = table;
    return table;
  } else {
    return found->second;
  }
}