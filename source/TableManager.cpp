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

bool Retsu::TableManager::exists(const string& table_name) {
  return fs::exists(fs::path(".") / table_name);
}

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

void Retsu::TableManager::drop(const string& table_name) {
  if(exists(table_name)) {
    string key = (fs::path(".") / table_name).string();
    TableCache::iterator found = table_cache.find(key);
    
    if(found != table_cache.end()) {
      table_cache.erase(key);
      found->second.reset();
    }
    
    fs::remove_all(key);
  }
}